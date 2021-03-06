
#option(MB_LUA "Enable the use of Lua components in your application" ON)
option(LUA_EDITOR_TOOL "Enable the Lua live editor" OFF)

#
#	Set the Sources and headers and forms
#

set ( MoleBox_SOURCES

  Actions/keyboard.cpp 
  Actions/mouse.cpp 
  action.cpp 
  actions.cpp
  Lua/content.cpp	  
  Lua/LuaScriptHelper.cpp
  Lua/Component.cpp
  Lua/luascript.cpp
  Lua/luascripts.cpp
  Lua/luaeditor.cpp 
  GameComponent.cpp
  Game.cpp
  Content.cpp

  )
  
  set ( MoleBox_HEADERS

  Lua/luaeditor.h
  Lua/LuaScriptHelper.h
  Lua/Component.h
  Lua/luascript.h
  Lua/luascripts.h
  ContentTemplate.h
  Content.h
  action.h
  actions.h
  ContainerDefinitions.h
  Content.h
  Game.h
  GameComponent.h
  Actions/keyboard.h
  Actions/mouse.h

  )
  
 set( MB_LIBS ${SFML_LIBRARIES} ${OPENGL_gl_LIBRARY} ${GLU_LIBRARY} ${LUA_LIBRARY} )
 #set( MB_INC_DIR ${CMAKE_CURRENT_BINARY_DIR} ${SFML_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLU_INCLUDE_PATH} ${LUA_INCLUDE_DIR})
 set (MB_FILE_LIST ${MoleBox_SOURCES})
 
  if (LUA_EDITOR_TOOL)
  
	set ( MoleBox_FORMS 
	      Lua/GameLuaEditor.ui
		)
	
	#set ( paulsframework_RESOURCES )
 
	qt4_wrap_cpp( MoleBox_HEADERS_MOC ${MoleBox_HEADERS} )
	qt4_wrap_ui( MoleBox_FORMS_HEADERS ${MoleBox_FORMS} )
	# qt_add_resources( paulsframework_RESOURCES_RCC ${paulsframework_RESOURCES} )

	add_definitions( "-DLUA_EDITOR" )
	#include_directories(${CMAKE_CURRENT_BINARY_DIR})
	add_definitions(${QT_DEFINITIONS})
	#set (MB_INC_DIR ${MB_INC_DIR} )
	set (MB_LIBS ${MB_LIBS} ${QT_LIBRARIES})
	set (MB_FILE_LIST 
			${MB_FILE_LIST}
			${MoleBox_HEADERS_MOC}
			${MoleBox_FORMS_HEADERS}
			#${paulsframework_RESOURCES_RCC}
		)
  endif()
  
  if (SFML_FOUND)
  
	message( ${MB_LIBS} )
  	add_library(MoleBox SHARED ${MB_FILE_LIST})

	include_directories(${CMAKE_CURRENT_BINARY_DIR} ${SFML_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLU_INCLUDE_PATH} ${LUA_INCLUDE_DIR})
	target_link_libraries(MoleBox ${MB_LIBS})

  endif()

  add_subdirectory(Lua)
add_subdirectory(Actions)