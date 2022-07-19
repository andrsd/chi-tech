#include "../lbkes_k_eigenvalue_solver.h"

#ifdef CHITECH_HAVE_LUA

#include <chi_lua.h>
#include "lbkes_lua_utils.h"

#include <chi_log.h>
;

#define MAX_ITERATIONS  1
#define TOLERANCE       2

using namespace lbs;

//############################################################
/**Set properties for the solver.*/
int chiLBKESSetProperty(lua_State *L)
{
  int num_args = lua_gettop(L);
  if (num_args < 2)
    LuaPostArgAmountError(__FUNCTION__, 2, num_args);

  LuaCheckNilValue(__FUNCTION__, L, 1);
  int solver_index = lua_tonumber(L, 1);
  auto& solver = lbs::k_eigenvalue_lua_utils::
  GetSolverByHandle(solver_index, __FUNCTION__);

  //============================================= Get property index
  LuaCheckNilValue(__FUNCTION__, L, 2);
  int property = lua_tonumber(L,2);

  //============================================= Handle properties
  if (property == MAX_ITERATIONS)
  {
    LuaCheckNilValue(__FUNCTION__, L, 3);
    int max_iters = lua_tointeger(L, 3);

    if (max_iters <= 0)
    {
      chi::log.LogAllError()
          << __FUNCTION__ << ": Invalid max_iterations value. "
          << "Must be greater than 0.";
      chi::Exit(EXIT_FAILURE);
    }
    solver.max_iterations = static_cast<size_t>(max_iters);

    chi::log.Log()
        << "LinearBoltzmann::KEigenvalueSolver: "
        << "max_iterations set to " << solver.max_iterations << ".";
  }

  else if (property == TOLERANCE)
  {
    LuaCheckNilValue(__FUNCTION__, L, 3);
    double tol = lua_tonumber(L, 3);

    if (tol < 0.0 or tol > 1.0)
    {
      chi::log.LogAllError()
          << __FUNCTION__ << ": Invalid value for tolerance. "
          << "Must be in the range (0.0, 1.0].";
      chi::Exit(EXIT_FAILURE);
    }
    solver.tolerance = tol;

    char buff[100];
    sprintf(buff, "%.4e", tol);

    chi::log.Log()
        << "LinearBoltzmann::KEigenvalueSolver: "
        << "tolerance set to " << buff << ".";
  }
  else
  {
    chi::log.LogAllError()
        << __FUNCTION__ << ": Invalid property index.";
    chi::Exit(EXIT_FAILURE);
  }
  return 0;
}

#endif
