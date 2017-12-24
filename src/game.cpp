//
// Created by Avikam Agur on 10/11/2017.
//

#include "src/game.h"

namespace pong {
    game::game(const config& conf) :
            s { conf },
            exit_ {false},
            txt_drawer {}
    {
        // Intialize SDL.
        SDL_Init(SDL_INIT_EVERYTHING);

        // Don't show cursor.
        SDL_ShowCursor(0);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        /* Turn on double buffering with a 24bit Z buffer.
         * You may need to change this to 16 or 32 for your system */
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);

        std::cout << DM.w << ", " << DM.h << std::endl;
        auto size = (0 != conf.window_size) ? conf.window_size : DM.h;

        // Create window and renderer.
        window = SDL_CreateWindow("Pong",
                                  SDL_WINDOWPOS_UNDEFINED,  // Centered window.
                                  SDL_WINDOWPOS_UNDEFINED,  // Centered window.
                                  size, size,
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

        maincontext = SDL_GL_CreateContext(window);
        if (maincontext == nullptr) {
            std::cout << "Error initing opengl context " << SDL_GetError() << std::endl;
            throw std::runtime_error("maincontext init error");
        }

        // Create full screen
//         SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
//        SDL_Rect curBounds;
//        SDL_GetWindowPosition( window, &curBounds.x, &curBounds.y );
//        SDL_GetWindowSize( window, &curBounds.w, &curBounds.h );
//
//        int idx = SDL_GetWindowDisplayIndex( window );
//        SDL_Rect bounds;
//        SDL_GetDisplayBounds( idx, &bounds );
        SDL_SetWindowBordered( window, SDL_FALSE );
        auto pos_x = (conf.window_pos_x == -1) ? (DM.w - size) / 2 : conf.window_pos_x;
        auto pos_y = (conf.window_pos_y == -1) ? (DM.h - size) / 2 : conf.window_pos_y;

        SDL_SetWindowPosition( window, pos_x, pos_y);
//        SDL_SetWindowSize( window, bounds.w, bounds.h );
        opengl_init();
        printf("OpenGL version is (%s)\n", glGetString(GL_VERSION));

        // Needs to be initialized after we have an OpenGl context
        game_start_ = new game_start{conf, txt_drawer};
        arena_ = new arena{conf};
    }

    game::~game() {
        SDL_GL_DeleteContext(maincontext);
        delete arena_;
        delete game_start_;
        // Destroy  window.
        SDL_DestroyWindow(window);

        // Shuts down SDL.
        SDL_Quit();
    }

    void game::render() {
        SDL_GL_SetSwapInterval(1);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        game_start_->invalidate(s);
        game_start_->render(s);

        if (!(s.is_welcome || s.is_game_start || s.is_instructions)) {
            arena_->render(s);
        }

        /* Swap our back buffer to the front */
        SDL_GL_SwapWindow(window);
    }

    void game::play() {
        std::cout << "start playing" << std::endl;
        while (true) {
            auto event = env_.get_event();
            if (event == input_t::quit) {
                return;
            }
            if (event == input_t::toggle_fullscreen) {
                (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN) ?
                    SDL_SetWindowFullscreen(window, 0) : SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
            }

            s.update(event);
            render();

            // TODO: Get the amount of time we waited while polling and deduce how much time to delay
            SDL_Delay(2);
        }
    }
}
