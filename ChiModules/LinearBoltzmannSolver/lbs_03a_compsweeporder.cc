#include "lbs_linear_boltzmann_solver.h"
#include "ChiMesh/MeshHandler/chi_meshhandler.h"
#include "ChiMesh/VolumeMesher/chi_volumemesher.h"
#include "ChiMesh/VolumeMesher/Extruder/volmesher_extruder.h"

#include "ChiMath/Quadratures/product_quadrature.h"

#include "chi_mpi.h"
#include "chi_runtime.h"
#include "chi_log.h"
#include "ChiTimer/chi_timer.h"


;


typedef chi_mesh::sweep_management::AngleSet TAngleSet;
typedef chi_mesh::sweep_management::AngleSetGroup TAngleSetGroup;

#ifdef CHITECH_HAVE_LUA
#include "ChiConsole/chi_console.h"
#include "Groupset/lbs_groupset.h"
#endif

#include <iomanip>

//###################################################################
/**Initializes the sweep ordering for the given groupset.*/
void lbs::SteadySolver::ComputeSweepOrderings(LBSGroupset& groupset) const
{
  if (options.verbose_inner_iterations)
    chi::log.Log()
      << chi::program_timer.GetTimeString()
      << " Computing Sweep ordering.\n";

  //============================================= Clear sweep ordering
  groupset.sweep_orderings.clear();
  groupset.sweep_orderings.shrink_to_fit();

  auto& mesh_handler = chi_mesh::GetCurrentHandler();
  auto mesher = mesh_handler.volume_mesher;

  const auto parmetis_partitioning = chi_mesh::VolumeMesher::PartitionType::PARMETIS;

  bool no_cycles_parmetis_partitioning =
    (mesher->options.partition_type == parmetis_partitioning and
                                       (not groupset.allow_cycles));
  bool is_1D_geometry = options.geometry_type == GeometryType::ONED_SLAB;

  //============================================= Check possibility of cycles
  if (no_cycles_parmetis_partitioning and not is_1D_geometry and chi::mpi.process_count>1)
  {
    chi::log.LogAllError()
      << "When using PARMETIS type partitioning then groupset iterative method"
         " must be NPT_CLASSICRICHARDSON_CYCLES or NPT_GMRES_CYCLES";
    chi::Exit(EXIT_FAILURE);
  }

  //================================================== Compute sweep ordering
  switch (groupset.angleagg_method)
  {
    case AngleAggregationType::SINGLE:
      ComputeSweepOrderingsAngleAggSingle(groupset); break;
    case AngleAggregationType::POLAR:
      ComputeSweepOrderingsAngleAggPolar(groupset); break;
    case AngleAggregationType::AZIMUTHAL:
      ComputeSweepOrderingsAngleAggAzimuthal(groupset); break;
    default:
      throw std::logic_error(std::string(__FUNCTION__) +
                             " Invalid angle aggregation type.");
  }//switch on method

#ifdef CHITECH_HAVE_LUA
  // FIXME: When GetMemoryUsageInMB() is refactored out of ChiConsole, this
  // can be activated again
  if (options.verbose_inner_iterations)
    chi::log.Log()
      << chi::program_timer.GetTimeString()
      << " Done computing sweep orderings.           Process memory = "
      << std::setprecision(3)
      << chi::console.GetMemoryUsageInMB() << " MB";
#endif

}


void lbs::SteadySolver::ComputeSweepOrderingsAngleAggSingle(LBSGroupset& groupset) const
{
  if (options.verbose_inner_iterations)
    chi::log.Log()
      << chi::program_timer.GetTimeString()
      << " Computing Sweep ordering - Angle aggregation: Single";

  for (const auto& omega : groupset.quadrature->omegas)
  {
    const auto new_swp_order =
      chi_mesh::sweep_management::
      CreateSweepOrder(omega,
                       this->grid,
                       groupset.allow_cycles);
    groupset.sweep_orderings.emplace_back(new_swp_order);
  }
}


void lbs::SteadySolver::ComputeSweepOrderingsAngleAggPolar(LBSGroupset& groupset) const
{
  if (options.verbose_inner_iterations)
    chi::log.Log()
      << chi::program_timer.GetTimeString()
      << " Computing Sweep ordering - Angle aggregation: Polar";

  const auto mesher = chi_mesh::GetCurrentHandler().volume_mesher;

  if (options.geometry_type == GeometryType::ONED_SLAB ||
      options.geometry_type == GeometryType::TWOD_CARTESIAN ||
      (options.geometry_type == GeometryType::THREED_CARTESIAN &&
       typeid(*mesher) == typeid(chi_mesh::VolumeMesherExtruder)))
  {
    if (groupset.quadrature->type == chi_math::AngularQuadratureType::ProductQuadrature)
    {
      const auto product_quadrature =
        std::static_pointer_cast<chi_math::ProductQuadrature>(groupset.quadrature);

      const auto num_azi = product_quadrature->azimu_ang.size();
      const auto num_pol = product_quadrature->polar_ang.size();

      if (options.geometry_type == GeometryType::ONED_SLAB)
      {
        if (num_azi != 1)
        {
          chi::log.LogAllError()
            << "Incompatible number of azimuthal angles in quadrature set "
            << "for a 1D simulation.";
          chi::Exit(EXIT_FAILURE);
        }
      }
      else
      {
        if (num_azi < 4)
        {
          chi::log.LogAllError()
            << "Incompatible number of azimuthal angles in quadrature set "
            << "for a 2D or 3D simulation.";
          chi::Exit(EXIT_FAILURE);
        }
      }

      if ((num_pol < 2) || (num_pol % 2 != 0))
      {
        chi::log.LogAllError()
          << "Incompatible number of polar angles in quadrature set.";
        chi::Exit(EXIT_FAILURE);
      }

      //============================================= Create sweep ordering
      //                                              per azimuthal angle
      //                                              per hemisphere
      const unsigned int pa = num_pol/2;

      //=========================================== TOP HEMISPHERE
      for (unsigned int i = 0; i < num_azi; ++i)
      {
        const auto dir_idx = product_quadrature->GetAngleNum(pa-1, i);
        const auto new_swp_order =
          chi_mesh::sweep_management::
          CreateSweepOrder(product_quadrature->omegas[dir_idx],
                           this->grid,
                           groupset.allow_cycles);
        groupset.sweep_orderings.emplace_back(new_swp_order);
      }
      //=========================================== BOTTOM HEMISPHERE
      for (unsigned int i = 0; i < num_azi; ++i)
      {
        const auto dir_idx = product_quadrature->GetAngleNum(pa, i);
        const auto new_swp_order =
          chi_mesh::sweep_management::
          CreateSweepOrder(product_quadrature->omegas[dir_idx],
                           this->grid,
                           groupset.allow_cycles);
        groupset.sweep_orderings.emplace_back(new_swp_order);
      }
    }//if product quadrature
    else
    {
      chi::log.LogAllError()
        << "The simulation is not using \"LBSGroupset.ANGLE_AGG_SINGLE\", "
           "and therefore only certain angular quadrature types are supported. "
           "i.e., for now just AngularQuadratureType::ProductQuadrature.";
      chi::Exit(EXIT_FAILURE);
    }
  }
  else
  {
    chi::log.LogAllError()
      << "The simulation is not using \"LBSGroupset.ANGLE_AGG_SINGLE\", "
         "and therefore only certain geometry types are supported. i.e., "
         "GeometryType::ONED_SLAB, GeometryType::TWOD_CARTESIAN, "
         "GeometryType::THREED_CARTESIAN.";
    chi::Exit(EXIT_FAILURE);
  }
}


void lbs::SteadySolver::ComputeSweepOrderingsAngleAggAzimuthal(LBSGroupset& groupset) const
{
  if (options.verbose_inner_iterations)
    chi::log.Log()
      << chi::program_timer.GetTimeString()
      << " Computing Sweep ordering - Angle aggregation: Azimuthal";

  if (options.geometry_type == GeometryType::ONED_SPHERICAL ||
      options.geometry_type == GeometryType::TWOD_CYLINDRICAL)
  {
    if (groupset.quadrature->type == chi_math::AngularQuadratureType::ProductQuadrature)
    {
      const auto product_quadrature =
        std::static_pointer_cast<chi_math::ProductQuadrature>(groupset.quadrature);

      for (const auto& dir_set : product_quadrature->GetDirectionMap())
        for (const auto& dir_idx : {dir_set.second.front(), dir_set.second.back()})
        {
          const auto new_swp_order =
            chi_mesh::sweep_management::
            CreateSweepOrder(product_quadrature->omegas[dir_idx],
                             this->grid,
                             groupset.allow_cycles);
          groupset.sweep_orderings.emplace_back(new_swp_order);
        }
    }
    else
    {
      chi::log.LogAllError()
        << "The simulation is not using \"LBSGroupset.ANGLE_AGG_SINGLE\", "
           "and therefore only certain angular quadrature types are supported. "
           "i.e., for now just AngularQuadratureType::ProductQuadrature.";
      chi::Exit(EXIT_FAILURE);
    }
  }
  else
  {
    chi::log.LogAllError()
      << "The simulation is not using \"LBSGroupset.ANGLE_AGG_SINGLE\", "
         "and therefore only certain geometry types are supported. i.e., "
         "GeometryType::ONED_SPHERICAL, GeometryType::TWOD_CYLINDRICAL.";
    chi::Exit(EXIT_FAILURE);
  }
}
