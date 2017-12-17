//
// Created by Avikam Agur on 24/11/2017.
//


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <sstream>

#include "src/opengl.h"
#include "src/scenes/scene.h"
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
    static void debug_err() {
        auto er = glGetError();
        if (er == GL_INVALID_OPERATION) {
            std::cout << "gl Draw Error: invalid op" << std::endl;
        }

    }

    scene::scene(text_drawer& txt_drawer) :
        _txt_drawer { txt_drawer }
    {
        // Create Vertex Array Object
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // Create and compile the vertex shader
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSource, NULL);
        compile_shader(vertexShader);

        // Create and compile the fragment shader
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
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
                -0.5f, 0.5f,    1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // Top-left
                0.5f, 0.5f,     1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // Top-right
                0.5f, -0.5f,    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
                -0.5f, -0.5f,   1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
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

        glGenTextures(4, textures);


        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);

    };

    scene::~scene() {
        glDeleteTextures(4, textures);

        glDeleteProgram(shaderProgram);
        // delete elements buffer
        glDeleteBuffers(1, &ebo);
        // delete vertex buffer
        glDeleteBuffers(1, &vbo);
        // delete vertex array data
        glDeleteVertexArrays(1, &vao);
    }

    void scene::draw_text_in_texture(int tex_num, const std::string& s) {

        glActiveTexture(GL_TEXTURE0 + tex_num);
        glBindTexture(GL_TEXTURE_2D, textures[tex_num]);
        _txt_drawer.draw(s);

        //Set Some basic parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    void scene::render(pong::state& s) {
        glBindVertexArray(vao);
        glUseProgram(shaderProgram);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);

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

        // Score of p1:
        {
            glm::mat4 transformation = glm::mat4{1};
            transformation = glm::translate(transformation, glm::vec3 { 0.85f, 0.1f, 0 });
            transformation = glm::rotate(transformation, glm::radians(270.0f), glm::vec3 { .0f,.0f,1.0f });
            transformation = glm::scale(transformation, glm::vec3 { 0.125f, 0.125f, 0 });


            glUniform1i(uniTex, 0);
            glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(transformation));

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            debug_err();
        }

        // Score of p2:
        {
            glm::mat4 transformation = glm::mat4{1};
            transformation = glm::translate(transformation, glm::vec3 { 0.85f, -0.1f, 0 });
            transformation = glm::rotate(transformation, glm::radians(270.0f), glm::vec3 { .0f,.0f,1.0f });
            transformation = glm::scale(transformation, glm::vec3 { 0.125f, 0.125f, 0 });

            glUniform1i(uniTex, 1);
            glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(transformation));

            // Create a Vertex Buffer Object and copy the vertex data to i
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            debug_err();
        }

        // Who won?:
        if (s.is_game_over && s.curr_winner != nullptr) {
            glm::mat4 transformation = glm::mat4{1};
            transformation = glm::translate(transformation, glm::vec3 { 0.0, 0.5 * (s.curr_winner == &s.p1 ? 1 : -1), 0 });
            transformation = glm::scale(transformation, glm::vec3 { 1.0f, 0.2f, 0 });
            transformation = glm::rotate(transformation, glm::radians(180.0f) * (s.curr_winner == &s.p1 ? 1 : 0),  glm::vec3 {0,0,1});

            glUniform1i(uniTex, 2);
            glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(transformation));

            // Create a Vertex Buffer Object and copy the vertex data to i
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            debug_err();
        }

        // pause:
        if (s.is_player_pressed_paused) {
            glm::mat4 transformation = glm::mat4{1};
            transformation = glm::rotate(transformation, glm::radians(270.0f), glm::vec3 { .0f,.0f,1.0f });
            transformation = glm::scale(transformation, glm::vec3 { 0.6f, 0.25f, 0 });

            glUniform1i(uniTex, 3);
            glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(transformation));

            // Create a Vertex Buffer Object and copy the vertex data to i
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            debug_err();
        }
    }

    void scene::invalidate(const pong::state& s) {
        {
            std::ostringstream stream;
            stream << s.p1.score;
            draw_text_in_texture(0, stream.str());

        }
        {
            std::ostringstream stream;
            stream << s.p2.score;
            draw_text_in_texture(1, stream.str());

        }
        {
            if (s.is_game_over && s.curr_winner != nullptr) {
                draw_text_in_texture(2, "WIN");
            }
        }
        {
            if (s.is_paused) {
                draw_text_in_texture(3, "PAUSED");
            }
        }
    }

}
