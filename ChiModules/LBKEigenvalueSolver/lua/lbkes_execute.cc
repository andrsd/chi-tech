#include "ChiLua/chi_lua.h"
#include "lbkes_lua_utils.h"

#ifdef CHITECH_HAVE_LUA

//###################################################################
/**Executes the LBS solver.
\param SolverIndex int Handle to the solver.
 \ingroup LuaLBS
 */
int chiLBKESExecute(lua_State *L)
{
  //============================================= Get pointer to solver
  int solver_index = lua_tonumber(L,1);
  auto& lbkes_solver = lbs::k_eigenvalue_lua_utils::
  GetSolverByHandle(solver_index, __FUNCTION__);

  lbkes_solver.Execute();

  return 0;
}

#endif
