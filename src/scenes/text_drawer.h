//
// Created by Avikam Agur on 20/11/2017.
//

#ifndef CIRPONG_START_GAME_H
#define CIRPONG_START_GAME_H

#include <SDL2/SDL_ttf.h>                   // SDL font library.
#include <string>

namespace pong {
    class text_drawer {
        SDL_Color textColor;
        SDL_Color backgroundColor;
        TTF_Font * font;
    public:
        explicit text_drawer();
        ~text_drawer();
        void draw(const std::string&);
    };
}

#endif //CIRPONG_START_GAME_H
