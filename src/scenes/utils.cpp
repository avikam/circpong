//
// Created by Avikam Agur on 25/11/2017.
//

#include <OpenGL/gl3.h>
#include <iostream>
#include <vector>

namespace pong {
    void compile_shader(GLuint shader) {
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
}
