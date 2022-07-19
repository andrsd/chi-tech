#include "lbs_linear_boltzmann_solver.h"

#include "ChiMath/SpatialDiscretization/FiniteElement/PiecewiseLinear/pwl.h"

#include "chi_runtime.h"
#include "chi_log.h"
;

#ifdef CHITECH_HAVE_LUA
#include "ChiConsole/chi_console.h"
#endif


#include <iomanip>

void lbs::SteadySolver::InitializeSpatialDiscretization()
{
  using namespace chi_math::finite_element;
  chi::log.Log() << "Initializing spatial discretization.\n";
  discretization =
    chi_math::SpatialDiscretization_PWLD::New(grid, COMPUTE_CELL_MAPPINGS |
                                                    COMPUTE_UNIT_INTEGRALS);


#ifdef CHITECH_HAVE_LUA
  // FIXME: When GetMemoryUsageInMB() is refactored out of ChiConsole, this
  // can be activated again
  MPI_Barrier(MPI_COMM_WORLD);
  chi::log.Log()
    << "Cell matrices computed.                   Process memory = "
    << std::setprecision(3)
    << chi::console.GetMemoryUsageInMB() << " MB";
#endif
}
