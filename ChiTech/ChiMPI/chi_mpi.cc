#include "chi_mpi.h"

namespace chi_objects
{

MPI_Info& MPI_Info::GetInstance() noexcept
{
  return instance;
}

}
