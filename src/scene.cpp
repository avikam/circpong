//
// Created by Avikam Agur on 24/11/2017.
//

#include <OpenGl/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include "src/scene.h"


// Shader sources
const GLchar* vertexSource = R"glsl(
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
const GLchar* fragmentSource = R"glsl(
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
    static void compile_shader(GLuint shader) {
        glCompileShader(shader);

        GLint status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (status != GL_TRUE) {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
            std::cout << &errorLog[0];

            glDeleteShader(shader);
            throw std::runtime_error("Cant compile vertext shader");
        } else {
            std::cout << "Compiled successfully" << std::endl;
        }
    }

    static void debug_err() {
        auto er = glGetError();
        if (er == GL_INVALID_OPERATION) {
            std::cout << "glDrawArrays Error: invalid op" << std::endl;
        }

    }

    scene::scene() {
        //Set Blending
        //Required so that the alpha channels show up from the surface
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Create Vertex Array Object
        GLuint vao;
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

        GLuint vbo;
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
        GLuint ebo;
        glGenBuffers(1, &ebo);

        GLuint elements[] = {
                0, 3, 1,
                1, 2, 3
        };

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);


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
    };

    scene::~scene() {
        glDeleteProgram(shaderProgram);
        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);
    }

    void scene::draw_texture(const GLvoid *pixels, int width, int height, int tex_num) {
        // Load textures
        GLuint textures[2];
        glGenTextures(1, textures);

        glActiveTexture(GL_TEXTURE0 + tex_num);
        glBindTexture(GL_TEXTURE_2D, textures[tex_num]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);


        //Set Some basic parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        //Set up Sampler
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[tex_num]);
    }

    void scene::render() {
        GLint uniTex = glGetUniformLocation(shaderProgram, "tex");
        GLint uniTrans = glGetUniformLocation(shaderProgram, "trans");

        {
            glm::mat4 identity{1};

            auto t = glm::scale(
                    glm::translate(identity, glm::vec3(-0.7f, 0.85f, 0)),
                    glm::vec3(0.5, 0.125, 0));

            glUniform1i(uniTex, 0);
            glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(t));

            // Create a Vertex Buffer Object and copy the vertex data to i
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            debug_err();
        }
        {
            glm::mat4 identity{1};

            auto t = glm::scale(
                    glm::translate(identity, glm::vec3(0.7f, 0.85f, 0)),
                    glm::vec3(0.5, 0.125, 0));

            glUniform1i(uniTex, 1);
            glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(t));

            // Create a Vertex Buffer Object and copy the vertex data to i
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            debug_err();
        }
    }

}
