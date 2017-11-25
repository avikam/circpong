//
// Created by Avikam Agur on 25/11/2017.
//

#ifndef CIRPONG_UTILS_H
#define CIRPONG_UTILS_H

namespace pong {
    #define odd_sign(n) (1 - 2*( (n) & 1) )

    void compile_shader(GLuint shader);
}
#endif //CIRPONG_UTILS_H
