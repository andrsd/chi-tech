#include "fv.h"

#include <ChiMesh/MeshContinuum/chi_meshcontinuum.h>

#include "CellViews/fv_slab.h"
#include "CellViews/fv_polygon.h"
#include "CellViews/fv_polyhedron.h"

#include "chi_log.h"
#include "chi_mpi.h"
#include "CellViews/fv_cellbase.h"


//###################################################################
/**Adds a PWL Finite Element for each cell of the local problem.*/
void chi_math::SpatialDiscretization_FV::PreComputeCellSDValues()
{
  chi::log.Log0Verbose1()
    << "SpatialDiscretization_FV - Adding view of local continuum.";

  //================================================== Create empty view
  //                                                 for each cell
  if (!mapping_initialized)
  {
    cell_view_added_flags.resize(ref_grid->local_cells.size(),false);
    mapping_initialized = true;
  }


  //================================================== Swap views for
  //                                                   specified item_id
  for (const auto& cell : ref_grid->local_cells)
  {
    if (not cell_view_added_flags[cell.local_id])
    {
      //######################################### SLAB
      if (cell.Type() == chi_mesh::CellType::SLAB)
      {
        auto view = new chi_math::SlabFVValues(cell, *ref_grid);

        cell_fv_views.push_back(view);
        cell_view_added_flags[cell.local_id] = true;
      }

      //######################################### POLYGON
      if (cell.Type() == chi_mesh::CellType::POLYGON)
      {
        auto view = new chi_math::PolygonFVValues(cell, *ref_grid);

        cell_fv_views.push_back(view);
        cell_view_added_flags[cell.local_id] = true;
      }

      //######################################### POLYHEDRON
      if (cell.Type() == chi_mesh::CellType::POLYHEDRON)
      {
        auto view = new chi_math::PolyhedronFVValues(cell, *ref_grid);

        cell_fv_views.push_back(view);
        cell_view_added_flags[cell.local_id] = true;
      }
    }//if mapping not yet assigned
  }//for num cells
}//AddViewOfLocalContinuum

//###################################################################
/**Adds a PWL Finite Element for each cell of the local problem.*/
void chi_math::SpatialDiscretization_FV::
  PreComputeNeighborCellSDValues()
{
  chi::log.Log0Verbose1()
    << "SpatialDiscretization_FV - Adding view of neighbor continuums.";

  auto ghost_cells = ref_grid->GetGhostCells();

  neighbor_cells.clear();
  for (auto& cell_ptr : ghost_cells)
    neighbor_cells.insert(
      std::make_pair(cell_ptr->global_id,std::move(cell_ptr)));

  chi::log.Log0Verbose1()
    << "Number neighbor cells: " << neighbor_cells.size();

  chi::log.Log0Verbose1()
    << "Adding neighbor views";
  //================================================== Populate cell fe views
  for (auto& cell_pair : neighbor_cells)
  {
    const auto& cell = *cell_pair.second;
    //######################################### SLAB
    if (cell.Type() == chi_mesh::CellType::SLAB)
    {
      auto view = new chi_math::SlabFVValues(cell, *ref_grid);

      neighbor_cell_fv_views.insert(std::pair<uint64_t, chi_math::CellFVValues*>(
        cell.global_id,view));
    }

    //######################################### POLYGON
    if (cell.Type() == chi_mesh::CellType::POLYGON)
    {
      auto view = new chi_math::PolygonFVValues(cell, *ref_grid);

      neighbor_cell_fv_views.insert(std::pair<uint64_t, chi_math::CellFVValues*>(
        cell.global_id,view));
    }

    //######################################### POLYHEDRON
    if (cell.Type() == chi_mesh::CellType::POLYHEDRON)
    {
      auto view = new chi_math::PolyhedronFVValues(cell, *ref_grid);

      neighbor_cell_fv_views.insert(std::pair<uint64_t, chi_math::CellFVValues*>(
        cell.global_id,view));
    }
  }//for num cells


  chi::log.LogAllVerbose1()
    << "Number of neighbor cells added: "
    << neighbor_cell_fv_views.size();
}//AddViewOfNeighborContinuums

//###################################################################
/**Maps the cell index to a position stored locally.*/
chi_math::CellFVValues* chi_math::SpatialDiscretization_FV::MapFeView(uint64_t cell_local_index)
{
  chi_math::CellFVValues* value = nullptr;
  try { value = cell_fv_views.at(cell_local_index); }
  catch (const std::out_of_range& o)
  {
    chi::log.LogAllError()
      << "SpatialDiscretization_FV::MapFeView "
         "Failure to map Finite Volume View. The view is either not"
         "available or the supplied local index is invalid.";
   chi::Exit(EXIT_FAILURE);
  }

  return value;
}

//###################################################################
/**Maps the cell index to a position stored locally.*/
chi_math::CellFVValues* chi_math::SpatialDiscretization_FV::MapNeighborFeView(uint64_t cell_global_index)
{
  //=================================== First check locally
  if (ref_grid->IsCellLocal(cell_global_index))
  {
    auto& neighbor_cell = ref_grid->cells[cell_global_index];
    return MapFeView(neighbor_cell.local_id);
  }

  //=================================== Now check neighbor cells
  auto neighbor_location = neighbor_cell_fv_views.find(cell_global_index);

  if (neighbor_location != neighbor_cell_fv_views.end())
    return neighbor_cell_fv_views.at(cell_global_index);
  else
    throw std::logic_error(std::string(__FUNCTION__) +
                           " Mapping of neighbor cell failed.");


//  auto& cell = ref_grid->cells[cell_global_index];
//
//  if (cell.partition_id == chi::mpi.location_id)
//    return MapFeView(cell.local_id);
//  else
//  {
//    int index=0;
//    for (auto ncell : neighbor_cells)
//    {
//      if (ncell->global_id == cell_global_index)
//        break;
//      ++index;
//    }
//    return neighbor_cell_fv_views[index];
//  }
}