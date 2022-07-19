#ifndef CHITECH_LBS_CURVILINEAR_SOLVER_LUA_H
#define CHITECH_LBS_CURVILINEAR_SOLVER_LUA_H

#include "chi_lua.h"

#ifdef CHITECH_HAVE_LUA

int chiLBSCurvilinearCreateSolver(lua_State *L);

namespace lbs_curvilinear
{
  namespace lua_utils
  {
    void RegisterLuaEntities(lua_State *L);
  }//namespace lua_utils
}//namespace LinearBoltzmann

#endif

#endif //CHITECH_LBS_CURVILINEAR_SOLVER_LUA_H
