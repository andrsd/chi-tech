#include "diffusion_lua.h"

#ifdef CHITECH_HAVE_LUA

#define LUA_FMACRO1(x) lua_register(L, #x, x)

void diffusion_solver::lua_utils::RegisterLuaEntities(lua_State *L)
{
  LUA_FMACRO1(chiDiffusionCreateSolver);
  LUA_FMACRO1(chiDiffusionInitialize);
  LUA_FMACRO1(chiDiffusionExecute);
  LUA_FMACRO1(chiDiffusionSetProperty);
}

#endif
