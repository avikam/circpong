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


set(SOURCE_FILES
        main.cpp
        src/environment.cpp
        src/player.cpp
        src/ball.cpp
        src/game.cpp
        src/control.cpp)
add_executable(cirpong ${SOURCE_FILES})
target_link_libraries(cirpong ${EXTRA_LIBS} SDL2 SDL2_ttf)
