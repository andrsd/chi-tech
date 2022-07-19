#include "pwl.h"

#include "ChiMath/PETScUtils/petsc_utils.h"

//###################################################################
/**Get the number of local degrees-of-freedom.*/
size_t chi_math::SpatialDiscretization_PWLD::
  GetNumLocalDOFs(const chi_math::UnknownManager& unknown_manager)
{
  unsigned int N = unknown_manager.GetTotalUnknownStructureSize();

  return local_base_block_size*N;
}

//###################################################################
/**Get the number of global degrees-of-freedom.*/
size_t chi_math::SpatialDiscretization_PWLD::
  GetNumGlobalDOFs(const chi_math::UnknownManager& unknown_manager)
{
  unsigned int N = unknown_manager.GetTotalUnknownStructureSize();

  return globl_base_block_size*N;
}

//###################################################################
/**Develops a localized view of a petsc vector.*/
void chi_math::SpatialDiscretization_PWLD::
  LocalizePETScVector(Vec petsc_vector,
                      std::vector<double>& local_vector,
                      chi_math::UnknownManager& unknown_manager)
{
  auto grid = ref_grid;

//  if (type == chi_math::SpatialDiscretizationType::PIECEWISE_LINEAR_CONTINUOUS)
//  {
//    std::vector<int> global_indices;
//    for (auto& cell : grid->local_cells)
//    {
//      for (int vid : cell.vertex_ids)
//      {
//        int uk=-1;
//        for (const auto& unknown : unknown_manager->unknowns)
//        {
//          ++uk;
//          for (int c=0; c<unknown.num_components; ++c)
//          {
//            int ir = MapCFEMDOF(vid,unknown_manager,uk,c);
//
//            global_indices.push_back(ir);
//          }//for component
//        }//for unknown
//      }//for node
//    }//for cell
//
//    chi_math::PETScUtils::CopyGlobalVecToSTLvector(petsc_vector,
//                                                   global_indices,
//                                                   local_vector);
//  }//if PWLC
//  else if (type == chi_math::SpatialDiscretizationType::PIECEWISE_LINEAR_DISCONTINUOUS)
  {
    std::vector<int64_t> global_indices;
    for (auto& cell : grid->local_cells)
    {
      for (int i=0; i<cell.vertex_ids.size(); ++i)
      {
        int uk=-1;
        for (const auto& unknown : unknown_manager.unknowns)
        {
          ++uk;
          for (int c=0; c<unknown.num_components; ++c)
          {
            int ir = MapDOF(cell, i, unknown_manager, uk, c);

            global_indices.push_back(ir);
          }//for component
        }//for unknown
      }//for node
    }//for cell

    chi_math::PETScUtils::CopyGlobalVecToSTLvector(petsc_vector,
                                                   global_indices,
                                                   local_vector);
  }

}