//
// Created by Avikam Agur on 10/11/2017.
//

#ifndef CIRPONG_GAME_H
#define CIRPONG_GAME_H

#include "src/environment.h"

namespace pong {
    class game {
    private:
        environment env_;
        bool exit_;
    public:
        game();
        ~game();

        void play();
    };
}

#endif //CIRPONG_GAME_H
