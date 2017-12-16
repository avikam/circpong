//
// Created by Avikam Agur on 15/12/2017.
//

#ifndef CIRPONG_GAME_START_H
#define CIRPONG_GAME_START_H

#include "src/state.h"
#include "src/scenes/text_drawer.h"

namespace pong {
        class game_start {
            GLuint shaderProgram;

            GLuint vao;
            GLuint vbo;
            GLuint ebo[2];

            GLuint textures[2];

            text_drawer& _txt_drawer;

            void draw_text_in_texture(int tex_num, const std::string& s);
            public:
            explicit game_start(text_drawer& txt_drawer);
            ~game_start();
            void render(pong::state& s);

            void invalidate(const pong::state& s);
        };
}


#endif //CIRPONG_GAME_START_H
