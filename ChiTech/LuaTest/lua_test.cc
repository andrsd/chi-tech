#include "chi_lua.h"
#include "chi_runtime.h"

#ifdef CHITECH_HAVE_LUA

#include "lua_test.h"

#define LUA_FMACRO1(x) lua_register(L, #x, x)

#include "unit_tests.h"

#include <stdexcept>

//###################################################################
/**This is a lua test function.
\param argument1 Any Argument of any type.
\ingroup LuaGeneralUtilities
 */
int chiLuaTest(lua_State* L)
{
  const int num_args = lua_gettop(L);
  bool verbose = false;
  if (num_args >= 1)
    verbose = lua_toboolean(L,1);

  chi_unit_tests::Test_chi_math(verbose);
  chi_unit_tests::Test_chi_misc_utils(verbose);
  chi_unit_tests::Test_chi_data_types(verbose);

  return 0;
}


int chiThrowException(lua_State* L)
{
  const std::string fname = __FUNCTION__;
  const int num_args = lua_gettop(L);

  std::string message = "Unknown exception thrown by " + fname;
  if (num_args == 1)
  {
    LuaCheckStringValue(fname, L, 1);
    message = lua_tostring(L,1);
  }

  throw std::logic_error(message);
}
int chiThrowRecoverableException(lua_State* L)
{
  const std::string fname = __FUNCTION__;
  const int num_args = lua_gettop(L);

  std::string message = "Unknown exception thrown by " + fname;
  if (num_args == 1)
  {
    LuaCheckStringValue(fname, L, 1);
    message = lua_tostring(L,1);
  }

  throw chi::RecoverableException(message);
}

void chi_lua_test::lua_utils::RegisterLuaEntities(lua_State *L)
{
  LUA_FMACRO1(chiLuaTest);
  LUA_FMACRO1(chiThrowException);
  LUA_FMACRO1(chiThrowRecoverableException);
}

#endif
