#include "luaScriptHelper.h"
// extracts a table into a std::map with provided types

bool TypeCheck(lua_State *L,int index,int type) {

  return (bool)(lua_type(L,index) == type);
  
}

void HandelError(lua_State *L,int status) {
  
  if ( status!=0 ) {
    
    std::cerr << "Script error: " << lua_tostring(L, -1) << std::endl;

    lua_pop(L, 1); // remove error message
    
  }
  
}

template<class T> T LuaReturnType(lua_State* L, int index)
{

  throw std::string("Feature not supported.");

}

template <> std::string LuaReturnType< std::string >(lua_State* L, int index)
{

  std::string outputString;
  outputString = lua_tostring(L,index);
  return outputString;

}

template <> bool LuaReturnType< bool >(lua_State* L, int index)
{

  return lua_toboolean(L, index);
}


template <> double LuaReturnType< double >(lua_State* L, int index)
{
  return lua_tonumber(L,index);
}

template <> int LuaReturnType< int >(lua_State* L, int index)
{
  return lua_tointeger(L,index);
}