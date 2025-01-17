#include "ChiLua/chi_lua.h"

#include "chi_mpi.h"

#ifdef CHITECH_HAVE_LUA

//#############################################################################
/** Blocks until all processes in the communicator have reached this routine.

\ingroup chiMPI
\author Jan*/
int chiMPIBarrier(lua_State *L)
{

  MPI_Barrier(MPI_COMM_WORLD);
  return 0;
}

#endif
