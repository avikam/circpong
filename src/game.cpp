//
// Created by Avikam Agur on 10/11/2017.
//

#include "src/game.h"

namespace pong {

    game::game() :
            exit_ {false}
    {
        // Intialize SDL.
        SDL_Init(SDL_INIT_EVERYTHING);

        // Don't show cursor.
        SDL_ShowCursor(0);

        // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        /* Turn on double buffering with a 24bit Z buffer.
         * You may need to change this to 16 or 32 for your system */
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


        // Create window and renderer.
        window = SDL_CreateWindow("Pong",
                                  SDL_WINDOWPOS_UNDEFINED,  // Centered window.
                                  SDL_WINDOWPOS_UNDEFINED,  // Centered window.
                                  constants::screen_width, constants::screen_height,
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

        maincontext = SDL_GL_CreateContext(window);
    }

    game::~game() {
        // Destroy  window.
        SDL_DestroyWindow(window);

        // Shuts down SDL.
        SDL_Quit();
    }

    void game::render() {
        SDL_GL_SetSwapInterval(1);
        //env_.render();
        start_game_.render();
        /* Swap our back buffer to the front */
        SDL_GL_SwapWindow(window);
    }

    void game::play() {
        while (env_.is_active()) {
            render();
            env_.update();
            env_.frame_delay();
            env_.get_event();
        }
    }
}