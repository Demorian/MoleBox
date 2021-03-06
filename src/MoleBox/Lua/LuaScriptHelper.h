/*
    Copyright (c) 2012 Paul Brown mafiamole@gmail.com

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

#ifndef LUASCRIPTHELPER
#define LUASCRIPTHELPER

extern "C" {
  #include "lua.hpp"
  #include "lualib.h"
  #include "lauxlib.h"
}

#include <iostream>
#include <string>
#include <map>

#include "../Content.h"



namespace LuaHelper {
  
  bool 					TypeCheck			( lua_State* L, int index , int type );
  void 					HandelError			( lua_State* L, int status );
  void					PushError			( lua_State* L, std::string errorString );

  template <class T> 	T 		LuaReturnType			( lua_State* L, int index );
  template <> 		std::string 	LuaReturnType <std::string>	( lua_State* L, int index );
  template <> 		bool 		LuaReturnType <bool>		( lua_State* L, int index );
  template <> 		int 		LuaReturnType <int>		( lua_State* L, int index );
  template <> 		double 		LuaReturnType <double>		( lua_State* L, int index );


  template <class K,class V> std::map<K,V> LuaMapTable( lua_State *L, std::string name, int valueType, int keyType ) {
    
    lua_getglobal(L,name.c_str());
    
    LuaMapTable<K,V>(L,valueType,keyType);
    
  }

  template <class K,class V> std::map<K,V> LuaMapTable( lua_State *L, int valueType, int keyType ) {
    
    std::map<K,V> outputMap;
    
    if ( !lua_istable( L, -1 ) )
      throw std::string("Type is not a table");
    
    for ( lua_pushnil(L); lua_next(L,-2); lua_pop(L,1) ) {
      
      if ( !LuaHelper::TypeCheck( L, -1, valueType ) )
	throw std::string("Value type was not expected in table.");

      
      if ( !LuaHelper::TypeCheck(L, -2, keyType) )
	throw std::string("Key type was not expected in table.");
      
      std::pair<K,V> test(  LuaReturnType<K>(L,-2),LuaReturnType<V>(L,-1));
      
      outputMap.insert(test);   
      
    }
    
    return outputMap;
    
  }


  
}
#endif