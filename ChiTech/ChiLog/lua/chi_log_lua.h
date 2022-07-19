#ifndef CHITECH_CHI_LOG_LUA_H
#define CHITECH_CHI_LOG_LUA_H

#include "chi_lua.h"

#ifdef CHITECH_HAVE_LUA

namespace chi_log_utils::lua_utils
  {
    void RegisterLuaEntities(lua_State* L);
  }//namespace chi::log_utils

#endif

#endif //CHITECH_chi::log_LUA_H
