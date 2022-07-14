#include "ChiLua/chi_lua.h"

#ifdef CHITECH_HAVE_LUA

#include "../lbs_linear_boltzmann_solver.h"
#include "ChiPhysics/chi_physics.h"
#include <chi_log.h>

extern ChiPhysics&  chi_physics_handler;
extern ChiLog& chi_log;

//###################################################################
/**Creates a Neutral Particle Transport solver.

\param SolverName string String name of the solver.

\return SolverHandle int Handle to the solver created.

\code
phys1 = chiLBSCreateSolver()
chiSolverAddRegion(phys1,region1)
--
-- Add Groupset construction here
--
chiLBSSetProperty(phys1,DISCRETIZATION_METHOD,PWLD)
chiLBSSetProperty(phys1,SCATTERING_ORDER,1)
--
chiLBSInitialize(phys1)
chiLBSExecute(phys1)
--
fflist,count = chiLBSGetScalarFieldFunctionList(phys1)
\endcode


\ingroup LuaLBS
 */
int chiLBSCreateSolver(lua_State *L)
{
  const std::string fname = __FUNCTION__;
  int num_args = lua_gettop(L);

  chi_log.Log(LOG_ALLVERBOSE_1) << "Creating Linear Boltzman solver";

  std::string solver_name = "LBSolver";
  if (num_args == 1)
  {
    LuaCheckStringValue(fname, L, 1);
    solver_name = lua_tostring(L, 1);
  }

  auto new_solver = new lbs::SteadySolver(solver_name);

  chi_physics_handler.solver_stack.push_back(new_solver);

  lua_pushinteger(L,
      static_cast<lua_Integer>(chi_physics_handler.solver_stack.size()-1));
  return 1;
}

#endif
