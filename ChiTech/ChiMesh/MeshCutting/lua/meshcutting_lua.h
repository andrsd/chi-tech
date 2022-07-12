#ifndef CHITECH_MESHCUTTING_LUA_H
#define CHITECH_MESHCUTTING_LUA_H

#include "chi_lua.h"

#ifdef CHITECH_HAVE_LUA

int chiCutMesh(lua_State* L);
int chiCountMeshInLogicalVolume(lua_State* L);

#endif

#endif //CHITECH_MESHCUTTING_LUA_H
