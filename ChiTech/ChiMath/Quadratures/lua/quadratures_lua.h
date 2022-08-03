#ifndef CHITECH_QUADRATURES_LUA_H
#define CHITECH_QUADRATURES_LUA_H

#ifdef CHITECH_HAVE_LUA

int chiCreateCustomAngularQuadrature(lua_State *L);
int chiCreateCylindricalProductQuadrature(lua_State *L);
int chiCreateSphericalProductQuadrature(lua_State *L);
int chiCreateProductQuadrature(lua_State *L);
int chiCreateQuadrature(lua_State *L);
int chiGetProductQuadrature(lua_State *L);

#endif

#endif //CHITECH_QUADRATURES_LUA_H
