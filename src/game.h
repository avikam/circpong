//
// Created by Avikam Agur on 10/11/2017.
//

#ifndef CIRPONG_GAME_H
#define CIRPONG_GAME_H

#include "src/state.h"

#include "src/environment.h"
#include "src/scenes/text_drawer.h"
#include "src/scenes/arena.h"
#include "src/scenes/game_start.h"

namespace pong {
    class game {
    private:
        environment env_;
        text_drawer txt_drawer;
        arena* arena_;
        game_start* game_start_;

        bool exit_;
        SDL_Window * window;
        SDL_GLContext maincontext; /* Our opengl context handle */

        void render();

        state s;
    public:
        game();
        ~game();

        void play();
    };
}

#endif //CIRPONG_GAME_H
