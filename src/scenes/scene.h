//
// Created by Avikam Agur on 24/11/2017.
//

#ifndef CIRPONG_SCENE_H
#define CIRPONG_SCENE_H

#include <OpenGL/gl3.h>
#include "src/text_drawer.h"
#include "src/state.h"

namespace pong{
    class scene {
        GLuint shaderProgram;
        GLuint fragmentShader;
        GLuint vertexShader;

        GLuint vao;
        GLuint vbo;
        GLuint ebo;

        text_drawer& _txt_drawer;

        void draw_texture(int tex_num, int score);
    public:
        explicit scene(text_drawer& txt_drawer);
        ~scene();
        void render(pong::state& s);

        void invalidate(const pong::state& s);
    };
}

#endif //CIRPONG_SCENE_H
