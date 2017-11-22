//
// Created by Avikam Agur on 20/11/2017.
//

#ifndef CIRPONG_START_GAME_H
#define CIRPONG_START_GAME_H

#include <SDL2/SDL_ttf.h>                   // SDL font library.

namespace pong {

    class start_game {
        SDL_Color textColor;
        SDL_Color backgroundColor;
        SDL_Surface* score_text;
    public:

        start_game();
        ~start_game();
        void render();
    };
}

#endif //CIRPONG_START_GAME_H
