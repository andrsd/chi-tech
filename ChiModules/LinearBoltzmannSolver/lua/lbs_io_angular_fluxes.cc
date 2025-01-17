#include "ChiLua/chi_lua.h"

#ifdef CHITECH_HAVE_LUA

#include "lbs_lua_utils.h"

#include "chi_runtime.h"
#include "chi_log.h"
#include "LinearBoltzmannSolver/Groupset/lbs_groupset.h"

//###################################################################
/**Writes the angular fluxes of a LBS groupset to file.

\param SolverIndex int Handle to the solver for which the group
is to be created.

\param GroupsetIndex int Index to the groupset to which this function should
                         apply

\param file_base string Path+Filename_base to use for the output. Each location
                        will append its id to the back plus an extension ".data"

*/
int chiLBSWriteGroupsetAngularFlux(lua_State *L)
{
  //============================================= Get arguments
  int num_args = lua_gettop(L);
  if (num_args != 3)
    LuaPostArgAmountError(__FUNCTION__,3,num_args);

  LuaCheckNilValue(__FUNCTION__,L,1);
  LuaCheckNilValue(__FUNCTION__,L,2);
  LuaCheckNilValue(__FUNCTION__,L,3);

  int      solver_index = lua_tonumber(L,1);
  int      grpset_index = lua_tonumber(L,2);
  std::string file_base = lua_tostring(L,3);

  //============================================= Get pointer to solver
  auto& lbs_solver = lbs::lua_utils::
    GetSolverByHandle(solver_index, __FUNCTION__);

  //============================================= Obtain pointer to groupset
  lbs::LBSGroupset* groupset = nullptr;
  try{
    groupset = &lbs_solver.groupsets.at(grpset_index);
  }
  catch (const std::out_of_range& o)
  {
    chi::log.LogAllError()
      << "Invalid handle to groupset "
      << "in call to " << __FUNCTION__;
    chi::Exit(EXIT_FAILURE);
  }

  lbs_solver.WriteGroupsetAngularFluxes(*groupset, file_base);

  return 0;
}

//###################################################################
/**Reads the angular fluxes of a LBS groupset from a file.

\param SolverIndex int Handle to the solver for which the group
is to be created.

\param GroupsetIndex int Index to the groupset to which this function should
                         apply

\param file_base string Path+Filename_base to use for the output. Each location
                        will append its id to the back plus an extension ".data"

*/
int chiLBSReadGroupsetAngularFlux(lua_State *L)
{
  //============================================= Get arguments
  int num_args = lua_gettop(L);
  if (num_args != 3)
    LuaPostArgAmountError(__FUNCTION__,3,num_args);

  LuaCheckNilValue(__FUNCTION__,L,1);
  LuaCheckNilValue(__FUNCTION__,L,2);
  LuaCheckNilValue(__FUNCTION__,L,3);

  int      solver_index = lua_tonumber(L,1);
  int      grpset_index = lua_tonumber(L,2);
  std::string file_base = lua_tostring(L,3);

  //============================================= Get pointer to solver
  auto& lbs_solver = lbs::lua_utils::
    GetSolverByHandle(solver_index, __FUNCTION__);

  //============================================= Obtain pointer to groupset
  lbs::LBSGroupset* groupset = nullptr;
  try{
    groupset = &lbs_solver.groupsets.at(grpset_index);
  }
  catch (const std::out_of_range& o)
  {
    chi::log.LogAllError()
      << "Invalid handle to groupset "
      << "in call to " << __FUNCTION__;
    chi::Exit(EXIT_FAILURE);
  }

  lbs_solver.ReadGroupsetAngularFluxes(*groupset, file_base);

  return 0;
}

#endif
