//
// Created by Avikam Agur on 25/11/2017.
//

#ifndef CIRPONG_ARENA_H
#define CIRPONG_ARENA_H

#include "src/state.h"
#include <OpenGl/gl3.h>

namespace pong {
    class arena {
        GLint arenaShaderProgram;
        GLint playerShaderProgram;
        GLuint vao;
        GLuint vbo[2];
    public:
        void render(state s);

        arena();
        ~arena();
    };
}

#endif //CIRPONG_ARENA_H
