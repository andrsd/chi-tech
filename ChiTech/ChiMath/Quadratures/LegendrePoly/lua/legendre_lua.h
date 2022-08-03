#ifndef LEGENDRE_LUA_H
#define LEGENDRE_LUA_H

#ifdef CHITECH_HAVE_LUA

int chiLegendre(lua_State *L);
int chiLegendreDerivative(lua_State *L);
int chiYlm(lua_State* L);

#endif

#endif //LEGENDRE_LUA_H
