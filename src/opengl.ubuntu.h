//
// Created by Avikam Agur on 15/12/2017.
//

#ifndef CIRPONG_OPENGL_UBUNTU_H
#define CIRPONG_OPENGL_UBUNTU_H

#include <OpenGl/glew.h>
#include <OpenGl/glext.h>

#define opengl_init() { \
    glewExperimental = GL_TRUE; \
    GLenum err = glewInit(); \
    if (GLEW_OK != err) { \
        /* Problem: glewInit failed, something is seriously wrong. */ \
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err)); \
        throw std::runtime_error("Cant init glew"); \
    } \
    if(!GLEW_ARB_vertex_array_object) { \
        std::cout << "ARB_vertex_array_object not available." << std::endl; \
        throw std::runtime_error("Cant use needed extension"); \
    } \
}

#endif //CIRPONG_OPENGL_UBUNTU_H
