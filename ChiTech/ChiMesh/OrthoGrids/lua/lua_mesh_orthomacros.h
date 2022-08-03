#ifndef CHITECH_LUA_MESH_ORTHOMACROS_H
#define CHITECH_LUA_MESH_ORTHOMACROS_H

#ifdef CHITECH_HAVE_LUA

int chiMeshCreateUnpartitioned1DOrthoMesh(lua_State* L);
int chiMeshCreateUnpartitioned2DOrthoMesh(lua_State* L);
int chiMeshCreateUnpartitioned3DOrthoMesh(lua_State* L);

#endif

#endif //CHITECH_LUA_MESH_ORTHOMACROS_H
