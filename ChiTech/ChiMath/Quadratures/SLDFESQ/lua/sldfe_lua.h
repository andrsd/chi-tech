#ifndef CHITECH_SLDFE_LUA_H
#define CHITECH_SLDFE_LUA_H

#include "chitech_config.h"

#ifdef CHITECH_HAVE_LUA

int chiCreateSLDFESQAngularQuadrature(lua_State* L);
int chiLocallyRefineSLDFESQAngularQuadrature(lua_State* L);
int chiPrintToPythonSLDFESQAngularQuadrature(lua_State* L);

#endif

#endif //CHITECH_SLDFE_LUA_H
