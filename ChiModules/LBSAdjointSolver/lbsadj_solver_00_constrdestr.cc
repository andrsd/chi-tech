#include "lbsadj_solver.h"

//###################################################################
/**Constructor.*/
lbs_adjoint::AdjointSolver::AdjointSolver(MPI_Comm in_comm, const std::string &solver_name) :
  lbs::SteadySolver(in_comm, solver_name)
{
  basic_options.AddOption<std::string>("REFERENCE_RF", std::string());
}
