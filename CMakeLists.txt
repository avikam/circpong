cmake_minimum_required(VERSION 3.5)
project(cirpong)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        .
        /usr/local/include/SDL2
)

IF(APPLE)
    FIND_LIBRARY(OPENGL OpenGL)
    MARK_AS_ADVANCED (OPENGL)
    SET(EXTRA_LIBS ${OPENGL})

    add_definitions(-DAPPLE)

ELSE()
    SET(EXTRA_LIBS GL GLEW)
ENDIF ()

if(UNIX AND NOT APPLE)
    # Use powermates controls, not on MAC :/
    SET(SRC_CONTROL src/control.cpp)

    # ADD_CUSTOM_TARGET(link_target ALL
    #   COMMAND ${CMAKE_COMMAND} -E create_symlink OpenGl /usr/include/GL)

else()
    SET(SRC_CONTROL src/control_non.cpp)
endif()


set(SOURCE_FILES
        src/main.cpp
        src/scenes/text_drawer.cpp
        src/scenes/utils.cpp


        src/scenes/arena.cpp
        src/scenes/game_start.cpp

        src/state.cpp
        src/environment.cpp
        src/player.cpp
        src/ball.cpp
        src/game.cpp
        ${SRC_CONTROL}
        src/input.h)
add_executable(cirpong ${SOURCE_FILES})
target_link_libraries(cirpong ${EXTRA_LIBS} SDL2 SDL2_ttf)
