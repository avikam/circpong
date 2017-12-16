//
// Created by Avikam Agur on 15/12/2017.
//

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <sstream>

#include "src/opengl.h"
#include "src/scenes/game_start.h"
#include "src/scenes/utils.h"

// Shader sources
static const GLchar* vertexSource = R"glsl(
    #version 150 core
    in vec2 position;
    in vec3 color;
    in vec2 texcoord;
    out vec3 Color;
    out vec2 Texcoord;
    uniform mat4 trans;
    void main()
    {
        Color = color;
        Texcoord = texcoord;
        gl_Position = trans * vec4(position, 0.0, 1.0);
    }
)glsl";

static const GLchar* fragmentSource = R"glsl(
    #version 150 core
    in vec3 Color;
    in vec2 Texcoord;
    out vec4 outColor;
    uniform sampler2D tex;
    void main()
    {
        outColor = texture(tex, Texcoord) * vec4(Color, 1);
    }
)glsl";

namespace pong {
    game_start::game_start(text_drawer &txt_drawer) :
            _txt_drawer{txt_drawer} {
        // Create Vertex Array Object
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // Create and compile the vertex shader
        auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSource, nullptr);
        compile_shader(vertexShader);

        // Create and compile the fragment shader
        auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
        compile_shader(fragmentShader);

        // Link the vertex and fragment shader into a shader program
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glBindFragDataLocation(shaderProgram, 0, "outColor");
        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);

        glGenBuffers(1, &vbo);

        GLfloat vertices[] = {
                //  Position      Color             Texcoords
                -0.5f, 0.5f,    1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // Top-left
                0.5f, 0.5f,     1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Top-right
                0.5f, -0.5f,    1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // Bottom-right
                -0.5f, -0.5f,   1.0f, 1.0f, 1.0f, 0.0f, 0.0f  // Bottom-left
        };

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Create an element array
        glGenBuffers(1, &ebo);

        GLuint elements[] = {
                0, 3, 1,
                1, 2, 3
        };

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

        glGenTextures(2, textures);

        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);

    }

    game_start::~game_start() {
        glDeleteTextures(2, textures);

        glDeleteProgram(shaderProgram);
        // delete elements buffer
        glDeleteBuffers(1, &ebo);
        // delete vertex buffer
        glDeleteBuffers(1, &vbo);
        // delete vertex array data
        glDeleteVertexArrays(1, &vao);
    }

    void game_start::draw_text_in_texture(int tex_num, const std::string& s) {

        glActiveTexture(GL_TEXTURE0 + tex_num);
        glBindTexture(GL_TEXTURE_2D, textures[tex_num]);
        _txt_drawer.draw(s);

        //Set Some basic parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    void game_start::invalidate(const pong::state &s) {
        auto secs = duration_cast<seconds>( high_resolution_clock::now() - s.game_start_time ).count();

        std::ostringstream stream;
        stream << (4 - secs);
        draw_text_in_texture(0, stream.str());
        draw_text_in_texture(1, "START GAME");

    }

    void game_start::render(pong::state &s) {
        glBindVertexArray(vao);
        glUseProgram(shaderProgram);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

        // Specify the layout of the vertex data
        // must happen AFTER binding vbo, otherwise glDrawArrays seems to be able draw on the account of
        // invalid op
        GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
        // uses currently bound vertex array object for the operation
        glEnableVertexAttribArray(posAttrib);
        glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), nullptr);

        GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
        glEnableVertexAttribArray(colAttrib);
        glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void *) (2 * sizeof(GLfloat)));

        GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
        glEnableVertexAttribArray(texAttrib);
        glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void *) (5 * sizeof(GLfloat)));


        GLint uniTex = glGetUniformLocation(shaderProgram, "tex");
        GLint uniTrans = glGetUniformLocation(shaderProgram, "trans");

        //Set Blending
        //Required so that the alpha channels show up from the surface
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // counter
        {
            glm::mat4 identity{1};

            auto t = glm::scale(identity, glm::vec3(0.5, -0.125, 0));

            glUniform1i(uniTex, 0);
            glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(t));

            // Create a Vertex Buffer Object and copy the vertex data to i
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    }
}