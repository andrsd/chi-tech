#ifndef CHITECH_SLDFE_LUA_H
#define CHITECH_SLDFE_LUA_H

#ifdef CHITECH_HAVE_LUA

int chiCreateSLDFESQAngularQuadrature(lua_State* L);
int chiLocallyRefineSLDFESQAngularQuadrature(lua_State* L);
int chiPrintToPythonSLDFESQAngularQuadrature(lua_State* L);

#endif

#endif //CHITECH_SLDFE_LUA_H
