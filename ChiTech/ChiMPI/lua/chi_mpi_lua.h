#ifndef CHITECH_CHI_MPI_LUA_H
#define CHITECH_CHI_MPI_LUA_H

#include "chi_lua.h"

#ifdef CHITECH_HAVE_LUA

int chiMPIBarrier(lua_State *L);

namespace chi_mpi_utils
{
  namespace lua_utils
  {
    void RegisterLuaEntities(lua_State* L);
  }//namespace lua_utils
}//namespace chi_mesh

#endif

#endif //CHITECH_CHI_MPI_LUA_H
