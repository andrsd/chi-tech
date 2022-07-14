#ifndef CHITECH_FIELDFUNCTIONS_LUA_H
#define CHITECH_FIELDFUNCTIONS_LUA_H

#include "chi_lua.h"

#ifdef CHITECH_HAVE_LUA

int chiGetFieldFunctionHandleByName(lua_State *L);
int chiGetFieldFunctionList(lua_State *L);
int chiExportFieldFunctionToVTK(lua_State *L);
int chiExportFieldFunctionToVTKG(lua_State *L);
int chiExportMultiFieldFunctionToVTK(lua_State *L);

#endif

#endif //CHITECH_FIELDFUNCTIONS_LUA_H
