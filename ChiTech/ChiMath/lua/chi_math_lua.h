#ifndef CHI_MATH_LUA_H
#define CHI_MATH_LUA_H

#include "chitech_config.h"

#ifdef CHITECH_HAVE_LUA

#include "chi_lua.h"

namespace chi_math
{
  namespace lua_utils
  {
    void RegisterLuaEntities(lua_State* L);
  }//namespace lua_utils
}//namespace chi_math

#endif

#endif //CHI_MATH_LUA_H
