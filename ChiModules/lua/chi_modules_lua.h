#ifndef CHITECH_CHI_MODULES_LUA_H
#define CHITECH_CHI_MODULES_LUA_H

#include "chi_lua.h"

#ifdef CHITECH_HAVE_LUA

namespace chi_modules
{
  namespace lua_utils
  {
    void RegisterLuaEntities(lua_State* L);
  }//namespace lua_utils
}

#endif

#endif //CHITECH_CHI_MODULES_LUA_H
