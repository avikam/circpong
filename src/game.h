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

        SDL_Window * window;
        SDL_GLContext maincontext; /* Our opengl context handle */

        void render();

    public:
        game();
        ~game();

        void play();
    };
}

#endif //CIRPONG_GAME_H
