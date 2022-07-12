#ifndef CHITECH_MESHHANDLER_LUA_H
#define CHITECH_MESHHANDLER_LUA_H

#include "chi_lua.h"

#ifdef CHITECH_HAVE_LUA

int chiMeshHandlerCreate(lua_State *L);
int chiMeshHandlerSetCurrent(lua_State *L);

#endif

#endif //CHITECH_MESHHANDLER_LUA_H
