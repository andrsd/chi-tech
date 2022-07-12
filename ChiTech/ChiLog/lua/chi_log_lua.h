#ifndef CHITECH_CHI_LOG_LUA_H
#define CHITECH_CHI_LOG_LUA_H

#include "chi_lua.h"

#ifdef CHITECH_HAVE_LUA

namespace chi_log_utils
{
  namespace lua_utils
  {
    void RegisterLuaEntities(lua_State* L);
  }//namespace lua_utils
}//namespace chi_log_utils

#endif

#endif //CHITECH_CHI_LOG_LUA_H
