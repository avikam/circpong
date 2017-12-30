//
// Created by Avikam Agur on 15/12/2017.
//

#ifndef CIRPONG_OPENGL_H
#define CIRPONG_OPENGL_H

#ifdef APPLE
    #include "src/opengl.mac.h"
#elif _WIN32
    #include "src/opengl.windows.h"
#else
    #include "src/opengl.ubuntu.h"
#endif

#endif //CIRPONG_OPENGL_H
