#include"../../../ChiLua/chi_lua.h"

#ifdef CHITECH_HAVE_LUA

#include "../chi_region.h"
#include "../../MeshHandler/chi_meshhandler.h"

/** \defgroup LuaRegion Regions
 * \ingroup LuaMesh
 */


//#############################################################################
/** Creates a new region mesh.

\return Handle int Handle to the created region.
\ingroup LuaRegion
\author Jan*/
int chiRegionCreate(lua_State *L)
{
  chi_mesh::MeshHandler* cur_hndlr = chi_mesh::GetCurrentHandler();

  chi_mesh::Region* new_region = new chi_mesh::Region;

  cur_hndlr->region_stack.push_back(new_region);

  lua_pushnumber(L,cur_hndlr->region_stack.size()-1);

  return 1;
}

#endif
