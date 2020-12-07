set(SDL2_IMAGE_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/SDL2_image/include")



if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
	set(SDL2_IMAGE_LIBRARIES ${CMAKE_CURRENT_LIST_DIR}/SDL2_image/lib/x64/SDL2_image.lib)
	file(GLOB SDL2_image_DLL ${CMAKE_CURRENT_LIST_DIR}/SDL2_image/lib/x64/*.dll)
else ()
	set(SDL2_IMAGE_LIBRARIES ${CMAKE_CURRENT_LIST_DIR}/SDL2_image/lib/x86/SDL2_image.lib)
	file(GLOB SDL2_image_DLL ${CMAKE_CURRENT_LIST_DIR}/SDL2_image/lib/x86/*.dll)
endif ()

string(STRIP "${SDL2_IMAGE_LIBRARIES}" SDL2_IMAGE_LIBRARIES)