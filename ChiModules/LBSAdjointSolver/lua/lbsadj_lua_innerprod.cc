#include "LBSAdjointSolver/lbsadj_solver.h"
#include "lbsadj_lua_utils.h"

#ifdef CHITECH_HAVE_LUA

namespace lbs_adjoint
{
namespace lua_utils
{

int chiAdjointSolverComputeInnerProduct(lua_State* L)
{
  const std::string fname = __FUNCTION__;
  const int num_args = lua_gettop(L);
  if (num_args != 1)
    LuaPostArgAmountError(fname, 1, num_args);

  LuaCheckNilValue(fname, L, 1);

  const int solver_index     = lua_tointeger(L,1);

  auto& solver = lbs_adjoint::lua_utils::GetSolverByHandle(solver_index,fname);

  const double ip_Q_phi_star = solver.ComputeInnerProduct();

  lua_pushnumber(L, ip_Q_phi_star);
  return 1;
}

}//namespace lua_utils
}//namespace lbs_adjoint

#endif
