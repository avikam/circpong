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
        GLint ballShaderProgram;
        GLint playerShaderProgram;
        GLuint vao;
        GLuint vbo[3];

        void render_player_set_pos(float angle, state::player_pos_t& player_pos_out);
        void render_ball(state::pos_t);
    public:
        void render(state& s);

        arena();
        ~arena();
    };
}

#endif //CIRPONG_ARENA_H
