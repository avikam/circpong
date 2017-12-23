//
// Created by Avikam Agur on 25/11/2017.
//

#ifndef CIRPONG_ARENA_H
#define CIRPONG_ARENA_H

#include "src/state.h"
#include "src/opengl.h"

namespace pong {
    class arena {
        GLint arenaShaderProgram;
        GLint ballShaderProgram;
        GLint playerShaderProgram;
        GLuint vao;
        GLuint vbo[3];

        const config& _conf;


        void render_player(player &p);
        void render_ball(pos_t);
    public:
        void render(state& s);

        explicit arena(const config& conf);
        ~arena();
    };
}

#endif //CIRPONG_ARENA_H
