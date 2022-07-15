#include "chi_mpi.h"

ChiMPI& ChiMPI::GetInstance() noexcept
{
  return instance;
}
