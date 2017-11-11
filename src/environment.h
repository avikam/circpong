//
// Created by Avikam Agur on 10/11/2017.
//

#ifndef CIRPONG_WINDOW_H
#define CIRPONG_WINDOW_H

#include <SDL2/SDL.h>                       // SDL library.
#include <SDL2/SDL_ttf.h>                   // SDL font library.
#include <SDL2/SDL_mixer.h>                 // SDL sound library.

namespace pong {
    class environment {
        SDL_Window * window;
        SDL_Renderer * renderer;
        SDL_GLContext maincontext; /* Our opengl context handle */
        unsigned int tick;
    public:
        environment();
        ~environment();

        void render();
        bool get_event();
        void frame_delay();
    };
}

#endif //CIRPONG_WINDOW_H
