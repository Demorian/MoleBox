/*
    Copyright (c) 2012 Paul Brown <email>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/


#ifndef LUASCRIPT_H
#define LUASCRIPT_H

#include "content.h"
#include "luascripts.h"
#include <lua.hpp>
#ifndef LUA_SFML_API
#define LUA_SFML_API
#include <sstream>

template <int T> static int voidLuaEmptyFunction(lua_State *L) {
  
  int n = lua_gettop(L);
  
  int numberOfArgs = T;
  
  if ( numberOfArgs != T)
  {
    
    std::string error;
    error = "Incorrect number of arguments, this function takes ";
    error += numberOfArgs;
    error += ".";
    lua_pushstring(L,error.c_str());
    lua_error(L);
  }
 
  return 0;
  
}

static const luaL_reg sprite_DUMMY[] =
{
  { "Load", voidLuaEmptyFunction<1> },
  { "Draw", voidLuaEmptyFunction<1> },
  { "Move", voidLuaEmptyFunction<3> },
  { "SetPosition", voidLuaEmptyFunction<3> },
  { "GetPosition", voidLuaEmptyFunction<0>},
  { NULL, NULL }
};

static const luaL_Reg sound_DUMMY[] =
{
  { "Load", voidLuaEmptyFunction<1>},
  { "Play", voidLuaEmptyFunction<1>},
  { NULL, NULL }
};

#endif

static const luaL_reg sprite[] =
{
  { "Load", MB_Lua::Sprites::Load},
  { "Draw", MB_Lua::Sprites::Draw},
  { "Move", MB_Lua::Sprites::Move},
  { "SetPosition", MB_Lua::Sprites::SetPosition},
  { "GetPosition", MB_Lua::Sprites::GetPosition},
  { NULL, NULL }
};

static const luaL_Reg sound[] =
{
  { "Load", MB_Lua::Sounds::Load},
  { "Play", MB_Lua::Sounds::Play},
  
  { NULL, NULL }
};
  
class LuaScript
{
private:
  lua_State *L;
  bool debug;
public:
    LuaScript(bool debug = false);
    bool LoadFromFile(std::string file);
    bool LoadFromString(std::string contents, std::string remarks = "");
    bool HandleError(int State);
    void RegisterComponentFunctions();
    void RegisterDummyComponentFuncs();
    bool RunScript();
    bool RunFunction(std::string name);
    bool LookForFunction( std::string name );
    std::string ErrorTypeName(int state);
    lua_State* GetState();
    virtual ~LuaScript();

};

#endif // LUASCRIPT_H
