#include "chi_ffinter_volume.h"
#include "chitech_config.h"

#include <chi_log.h>
extern ChiLog& chi_log;

#ifdef CHITECH_HAVE_LUA

#include "ChiConsole/chi_console.h"
extern ChiConsole&  chi_console;

//###################################################################
/**Calls the designated lua function*/
double chi_mesh::FieldFunctionInterpolationVolume::
  CallLuaFunction(double ff_value, int mat_id)
{
  lua_State* L  = chi_console.consoleState;
  double ret_val = 0.0;

  lua_getglobal(L,op_lua_func.c_str());
  lua_pushnumber(L,ff_value);
  lua_pushnumber(L,mat_id);

  //2 arguments, 1 result, 0=original error object
  if (lua_pcall(L,2,1,0) == 0)
  {
    ret_val = lua_tonumber(L,-1);
  }
  lua_pop(L,1);


  return ret_val;
}

#else

double chi_mesh::FieldFunctionInterpolationVolume::CallLuaFunction(double ff_value, int mat_id)
{
  chi_log.Log(LOG_ALLERROR) << "chi_mesh::FieldFunctionInterpolationVolume::CallLuaFunction: ChiTech was not built with Lua support.";
  exit(EXIT_FAILURE);
}

#endif
