#ifndef LEGENDRE_LUA_H
#define LEGENDRE_LUA_H

#include "chitech_config.h"

#ifdef CHITECH_HAVE_LUA

int chiLegendre(lua_State *L);
int chiLegendreDerivative(lua_State *L);
int chiYlm(lua_State* L);

#endif

#endif //LEGENDRE_LUA_H
