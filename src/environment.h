//
// Created by Avikam Agur on 10/11/2017.
//

#ifndef CIRPONG_WINDOW_H
#define CIRPONG_WINDOW_H

#include <SDL2/SDL.h>                       // SDL library.
// #include <SDL2/SDL_ttf.h>                   // SDL font library.
// #include <SDL2/SDL_mixer.h>                 // SDL sound library.

#include "src/ball.h"
#include "src/player.h"

namespace pong {
    enum class state_t {
        active,
        player1_win,
        player2_win,
        user_quit
    };

    class environment {
        SDL_Window * window;
        SDL_Renderer * renderer;
        SDL_GLContext maincontext; /* Our opengl context handle */
        int tick;
        double unit;
        void renderAndSetCoordinate(player &p);
        void render(const ball& p);

        bool turn_p1;

        state_t state ;
        player p1;
        player p2;
        ball b;

    public:
        environment();
        ~environment();

        void render();
        bool get_event();
        void update();
        void frame_delay();
        bool is_active();
    };
}

#endif //CIRPONG_WINDOW_H
