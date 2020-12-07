# CMakeList.txt : projet CMake pour ImageRetouche, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

project ("ImageRetouche")

if (WIN32)
	list(APPEND CMAKE_PREFIX_PATH ./SDL)
	list(APPEND CMAKE_PREFIX_PATH ./SDL/Release)
	list(APPEND CMAKE_PREFIX_PATH ./SDL/Debug)
	find_package(SDL2 REQUIRED)
	find_package(SDL2_ttf REQUIRED)
	find_package(SDL2_mixer REQUIRED)
	find_package(SDL2_image REQUIRED)
else()
	find_package(PkgConfig REQUIRED) 
	pkg_check_modules(SDL2 REQUIRED sdl2 SDL2_ttf SDL2_mixer SDL2_image)
endif()
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE})

set(SRCS "src/main.cpp")
set(HEADERS "headers/Panel" "headers/Draw" "headers/FrameRate" "headers/Input" "headers/library" "headers/Matrix" "headers/Point" "headers/Texture" "headers/Window" "headers/Render" "headers/Shape.h")



# Ajoutez une source à l'exécutable de ce projet.
add_executable(ImageRetouche  ${SRCS} ${HEADERS} "headers/Panel" "headers/Draw" "headers/FrameRate" "headers/Input" "headers/library" "headers/Matrix" "headers/Point" "headers/Texture" "headers/Window" "headers/Render" "headers/Shape.h")

target_include_directories(ImageRetouche PRIVATE headers)

target_link_libraries(ImageRetouche ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})


if (WIN32)
	file( 
	COPY ${SDL2_DLL} ${SDL2_mixer_DLL} ${SDL2_ttf_DLL} ${SDL2_image_DLL}
	DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
endif()
# TODO: Ajoutez des tests et installez des cibles si nécessaire.
