#include "lbs_linear_boltzmann_solver.h"

#include "ChiMath/SpatialDiscretization/FiniteElement/PiecewiseLinear/pwl.h"

#include "chi_log.h"
extern ChiLog& chi_log;

#ifdef CHITECH_HAVE_LUA
#include "ChiConsole/chi_console.h"
extern ChiConsole&  chi_console;
#endif

#include <iomanip>

void lbs::SteadySolver::InitializeSpatialDiscretization()
{
  using namespace chi_math::finite_element;
  chi_log.Log(LOG_0) << "Initializing spatial discretization.\n";
  discretization =
    SpatialDiscretization_PWLD::New(grid, COMPUTE_CELL_MAPPINGS |
                                          COMPUTE_UNIT_INTEGRALS);


#ifdef CHITECH_HAVE_LUA
  // FIXME: When GetMemoryUsageInMB() is refactored out of ChiConsole, this
  // can be activated again
  MPI_Barrier(MPI_COMM_WORLD);
  chi_log.Log(LOG_0)
    << "Cell matrices computed.                   Process memory = "
    << std::setprecision(3)
    << chi_console.GetMemoryUsageInMB() << " MB";
#endif
}
