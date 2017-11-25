//
// Created by Avikam Agur on 24/11/2017.
//

#ifndef CIRPONG_SCENE_H
#define CIRPONG_SCENE_H

#include <OpenGL/gl3.h>
#include "src/state.h"

namespace pong{
    class scene {
        GLuint shaderProgram;
        GLuint fragmentShader;
        GLuint vertexShader;

        GLuint vao;
        GLuint vbo;
        GLuint ebo;

    public:
        scene();
        ~scene();
        void draw_texture(const GLvoid *pixels, int width, int height, int tex_num);
        void render(pong::state s);
    };
}

#endif //CIRPONG_SCENE_H
