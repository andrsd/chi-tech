#include "lbs_linear_boltzmann_solver.h"
#include "ChiConsole/chi_console.h"

#include "ChiMesh/MeshHandler/chi_meshhandler.h"
#include "ChiMesh/VolumeMesher/Extruder/volmesher_extruder.h"

#include "chi_runtime.h"
#include "chi_log.h"
#include "chi_mpi.h"

#include <iomanip>

#include "ChiTimer/chi_timer.h"
#include "Groupset/lbs_groupset.h"





//###################################################################
/**Initializes fluds data structures.*/
void lbs::SteadySolver::InitFluxDataStructures(LBSGroupset& groupset)
{
  //================================================== Angle Aggregation
  auto& handler = chi_mesh::GetCurrentHandler();
  chi_mesh::VolumeMesher& mesher = *handler.volume_mesher;

  if ( options.geometry_type == GeometryType::ONED_SLAB or
       options.geometry_type == GeometryType::TWOD_CARTESIAN or
       (typeid(mesher) == typeid(chi_mesh::VolumeMesherExtruder)))
  {
    switch (groupset.angleagg_method)
    {
      case AngleAggregationType::SINGLE:
        InitAngleAggSingle(groupset); break;
      case AngleAggregationType::POLAR:
        InitAngleAggPolar(groupset); break;
      default:
        throw std::logic_error(std::string(__FUNCTION__) +
                               " Invalid angle aggregation type.");
    }//switch on method
  }//if aggregatable
  else if (options.geometry_type == GeometryType::ONED_SPHERICAL ||
           options.geometry_type == GeometryType::TWOD_CYLINDRICAL)
  {
    switch (groupset.angleagg_method)
    {
      case AngleAggregationType::SINGLE:
        InitAngleAggSingle(groupset); break;
      case AngleAggregationType::AZIMUTHAL:
        InitAngleAggAzimuthal(groupset); break;
      default:
        throw std::logic_error(std::string(__FUNCTION__) +
                               " Invalid angle aggregation type.");
    }//switch on method
  }//if aggregatable
  else
    InitAngleAggSingle(groupset);

#ifdef CHITECH_HAVE_LUA
  // FIXME: When GetMemoryUsageInMB() is refactored out of ChiConsole, this
  // can be activated again
  if (options.verbose_inner_iterations)
    chi::log.Log()
      << chi::program_timer.GetTimeString()
      << " Initialized Angle Aggregation.   "
      << "         Process memory = "
      << std::setprecision(3) << chi::console.GetMemoryUsageInMB()
      << " MB.";
#endif

  MPI_Barrier(MPI_COMM_WORLD);
}
