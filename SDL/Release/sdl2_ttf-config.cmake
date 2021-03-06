set(SDL2_TTF_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/SDL2_ttf/include")



if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
	set(SDL2_TTF_LIBRARIES ${CMAKE_CURRENT_LIST_DIR}/SDL2_ttf/lib/x64/SDL2_ttf.lib)
	file(GLOB SDL2_ttf_DLL ${CMAKE_CURRENT_LIST_DIR}/SDL2_ttf/lib/x64/*.dll)
else ()
	set(SDL2_TTF_LIBRARIES ${CMAKE_CURRENT_LIST_DIR}/SDL2_ttf/lib/x86/SDL2_ttf.lib)
	file(GLOB SDL2_ttf_DLL ${CMAKE_CURRENT_LIST_DIR}/SDL2_ttf/lib/x86/*.dll)
endif ()

string(STRIP "${SDL2_TTF_LIBRARIES}" SDL2_TTF_LIBRARIES)