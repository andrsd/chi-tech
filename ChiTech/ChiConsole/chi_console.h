#ifndef CHI_CONSOLE_H
#define CHI_CONSOLE_H

#include "chitech_config.h"

#ifdef CHITECH_HAVE_LUA

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
#include "chi_console_structs.h"

#include <vector>
#include <string>

//############################################################################# CLASS DEF
/** Class for handling the console and scripting.*/
class ChiConsole
{
public:
	lua_State*							consoleState;    ///< Pointer to lua console state
	bool                    exit_loop=false; ///< Console loop termination flag

	std::vector<std::string> command_buffer; ///< Buffer of commands to execute

private:
  static ChiConsole       instance;
	//00
						  ChiConsole() noexcept;
public:
	static ChiConsole& GetInstance() noexcept
  {return instance;}

  //01 Loop
  void        RunConsoleLoop(char* fileName=nullptr);
  //02 Utilities
  int         ExecuteFile(const char* fileName,int argc, char** argv) const;
  void        PostMPIInfo(int location_id, int number_of_processes) const;
  //03
  void        FlushConsole();
  //05 Memory
	// FIXME: Memory usage should not be part of console. It should be refactored into its own thing
  CSTMemory  GetMemoryUsage();
  double      GetMemoryUsageInMB();
};

#endif

#endif
