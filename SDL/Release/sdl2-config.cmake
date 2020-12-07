set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/SDL2/include")



if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
	set(SDL2_LIBRARIES ${CMAKE_CURRENT_LIST_DIR}/SDL2/lib/x64/SDL2.lib 		${CMAKE_CURRENT_LIST_DIR}/SDL2/lib/x64/SDL2main.lib)
	file(GLOB SDL2_DLL ${CMAKE_CURRENT_LIST_DIR}/SDL2/lib/x64/*.dll)
else ()
	set(SDL2_LIBRARIES ${CMAKE_CURRENT_LIST_DIR}/SDL2/lib/x86/SDL2.lib 		${CMAKE_CURRENT_LIST_DIR}/SDL2/lib/x86/SDL2main.lib)
	file(GLOB SDL2_DLL ${CMAKE_CURRENT_LIST_DIR}/SDL2/lib/x86/*.dll)
endif ()

string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)