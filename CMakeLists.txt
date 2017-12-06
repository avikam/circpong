cmake_minimum_required(VERSION 3.5)
project(cirpong)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        .
        /usr/local/include/SDL2
)

IF(APPLE)
    #SET(GUI_TYPE MACOSX_BUNDLE)
    FIND_LIBRARY(OPENGL OpenGL)
    MARK_AS_ADVANCED (OPENGL)
    SET(EXTRA_LIBS ${OPENGL})
ELSE()
    SET(EXTRA_LIBS GL)
ENDIF ()

if(UNIX AND NOT APPLE)
    # SET(SRC_CONTROL src/control.cpp)
    SET(SRC_CONTROL src/control_non.cpp)

    # ADD_CUSTOM_TARGET(link_target ALL
    #   COMMAND ${CMAKE_COMMAND} -E create_symlink OpenGl /usr/include/GL)

else()
    SET(SRC_CONTROL src/control_non.cpp)
endif()


set(SOURCE_FILES
        main.cpp
        src/scenes/utils.cpp
        src/scenes/scene.cpp
        src/scenes/arena.cpp

        src/state.cpp
        src/environment.cpp
        src/text_drawer.cpp
        src/player.cpp
        src/ball.cpp
        src/game.cpp
        ${SRC_CONTROL}
)
add_executable(cirpong ${SOURCE_FILES})
target_link_libraries(cirpong ${EXTRA_LIBS} SDL2 SDL2_ttf GLEW)

