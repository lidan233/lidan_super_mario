cmake_minimum_required(VERSION 3.14)
project(supermario)

set(CMAKE_CXX_STANDARD 14)
INCLUDE_DIRECTORIES(/usr/local/include/)
INCLUDE_DIRECTORIES(/Users/lidan/Desktop/LineClipping/LineClipping/includes/)
LINK_DIRECTORIES(/usr/local/lib/)

link_libraries(glfw3 GLEW SOIL SDL libSDLmain.a libSDL_image.a )


add_executable(supermario main.cpp ./src/textures.h ./src/textures.cpp ./src/game.h   ./src/game.cpp   )
#add_executable(supermario ./src/mario.cpp ./src/textures.h ./src/textures.cpp ./src/game.h   ./src/game.cpp   )

target_link_libraries(supermario
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo")
#        "-framework SDL")
