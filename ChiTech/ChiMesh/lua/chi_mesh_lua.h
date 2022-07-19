#ifndef CHITECH_CHI_MESH_LUA_H
#define CHITECH_CHI_MESH_LUA_H

#include "chi_lua.h"

#ifdef CHITECH_HAVE_LUA

namespace chi_mesh::lua_utils
  {
    void RegisterLuaEntities(lua_State* L);
  }//namespace chi_mesh

#endif

#endif //CHITECH_CHI_MESH_LUA_H
