#include "lbs_linear_boltzmann_solver.h"



//###################################################################
/**Constructor for LBS*/
lbs::SteadySolver::SteadySolver(MPI_Comm in_comm, const std::string& in_text_name) :
  chi_physics::Solver(in_comm, in_text_name)
{
  boundary_types.resize(6,
    std::pair<BoundaryType,int>(lbs::BoundaryType::VACUUM, -1));
}
