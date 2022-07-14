#ifndef CHITECH_XSECTIONS_LUA_UTILS_H
#define CHITECH_XSECTIONS_LUA_UTILS_H

#include "chi_lua.h"

#ifdef CHITECH_HAVE_LUA

int chiPhysicsTransportXSCreate(lua_State* L);
int chiPhysicsTransportXSSet(lua_State* L);
int chiPhysicsTransportXSMakeCombined(lua_State* L);
int chiPhysicsTransportXSSetCombined(lua_State* L);
int chiPhysicsTransportXSGet(lua_State* L);
int chiPhysicsTransportXSExportToChiTechFormat(lua_State* L);

#endif

#endif //CHITECH_XSECTIONS_LUA_UTILS_H
