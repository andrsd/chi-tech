/**\page DevManGlobalVars Global variables

\section devman2_sec0 Global variables available

All global entities for the ChiTech library are contained within the
static `chi` class. This class has the name `chi` and an instance of it
cannot be created. Within this class, all of its members are statically
declared. Several singleton objects are defined in `chi`, they are:
 - chi::mpi A handler for parallel related items.
 - chi::program_timer The primary program timer.
 - chi::console The link to the lua scripting engine.
 - chi::log A handler for parallel logging events and verbosity.

A number of stacks are also declared. They are basically arrays of
shared pointers (i.e., `std::shared_ptr`)

There are also a number of secondary global variables that assist developers
with coding. They are:
 - ChiTimer chi_program_timer Holds a timer which initiates at program
   start. To access the timer from another piece of source code, include at the
   top of the file the ```extern``` command:
   \code
   #include "ChiTimer/chi_timer.h"
   extern ChiTimer& chi_program_timer;
   \endcode
   Current program time can then be obtained using:
   \code
   double time_in_ms = chi_program_timer.GetTime();
   \endcode
 - ```std::string chi_input_file_name``` Holds the input file name if supplied.
 - ```bool chi_termination_posted``` A flag used during interactive mode.
 - ```bool chi_sim_option_interactive``` A flag indicating whether the code is
   run in interactive mode.
 - ```std::vector<chi_mesh::MeshHandler*> chi_meshhandler_stack``` and
   ```int chi_current_mesh_handler```. Holds various mesh handlers. When not using
   the lua code to create a chi_mesh::MeshHandler be sure to set it to current
   in order to ensure that the method chi_mesh::GetCurrentHandler() works:
   \code
   chi_meshhandler_stack.push_back(new chi_mesh::MeshHandler);
   int index = chi_meshhandler_stack.size()-1;

   chi_current_mesh_handler = index;
   \endcode
   And using it:
   \code
   auto& handler = *chi_mesh::GetCurrentHandler();
   \endcode




\subsection devman2_sec0_3 Connecting to the global data block

To be completed...

\subsection devman2_sec0_4 Connecting to MPI

General MPI information like the current location id and the total amount
 of parallel processes is contained in CHI_MPI:
 - ChiMPI::location_id
 - ChiMPI::process_count

Additionally, by including the headers for chi_mpi, developers have access to
 all the classic mpi headers.

\code
#include <chi_mpi.h>

extern ChiMPI& chi_mpi;

if (chi_mpi.location_id == 1)
 printf("This is process 1, Dab!");
\endcode

 or obtain an instance to it via

\code
// Include this at the top of the file
#include <chi_mpi.h>

// Include this in the body of your code
ChiMPI&      chi_mpi = ChiMPI::GetInstance();
\endcode


\subsection devman2_sec0_5 Connecting to the parallel logging utility

Printing information in a parallel environment can be a very involved
process. One can't simply use "std::cout <<" on every process otherwise
the output to the log will be chaotic. For this reason we employ a common
 logging utility which return an output string stream using the function
 call ChiLog::Log.

Connecting to chi::log is done as follows
\code
#include <chi::log.h>

extern ChiLog& chi::log;
\endcode

 or obtain an instance to it via

\code
// Include this at the top of the file
#include <chi::log.h>

// Include this in the body of your code
ChiLog&      chi::log = ChiLog::GetInstance();
\endcode

The logger needs to be supplied with an enumeration (LOG_LVL) indicating
 the type of output. The following enumerations are supported:
 - LOG_0,                      Used only for location 0
 - LOG_0WARNING,               Warning only for location 0
 - LOG_0ERROR,                 Error only for location 0
 - LOG_0VERBOSE_0,             Default verbosity level
 - LOG_0VERBOSE_1,             Used only if verbosity level equals 1
 - ChiLog::LOG_LVL::LOG_0VERBOSE_2,             Used only if verbosity level equals 2
 - LOG_ALL,                    Verbose level 0 all locations
 - LOG_ALLWARNING,             Warning for any location
 - LOG_ALLERROR,               Error for any location
 - LOG_ALLVERBOSE_0,     Default verbosity level
 - LOG_ALLVERBOSE_1,     Used only if verbosity level equals 1
 - LOG_ALLVERBOSE_2,     Used only if verbosity level equals 2



\todo Commandline parameter documentation


*/