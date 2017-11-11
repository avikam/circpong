//
// Created by Avikam Agur on 10/11/2017.
//

#include <SDL_opengl.h>
#include "src/environment.h"

namespace pong{
    static int SCREEN_WIDTH = 720;
    static int SCREEN_HEIGHT = 720;
    static double PI = 3.1415926535897932384626433832795;
    static float radius = 1;


    environment::environment() : tick {0} {
        // Intialize SDL.
        SDL_Init(SDL_INIT_EVERYTHING);

        // Don't show cursor.
        SDL_ShowCursor(0);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        /* Turn on double buffering with a 24bit Z buffer.
         * You may need to change this to 16 or 32 for your system */
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


        // Create window and renderer.
        window = SDL_CreateWindow("Pong",
                                  SDL_WINDOWPOS_UNDEFINED,  // Centered window.
                                  SDL_WINDOWPOS_UNDEFINED,  // Centered window.
                                  SCREEN_WIDTH,
                                  SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

        maincontext = SDL_GL_CreateContext(window);

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                                  SDL_RENDERER_PRESENTVSYNC);

        // Instantiate game objects.

    }

    environment::~environment() {
        // Destroy renderer and window.
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        // Shuts down SDL.
        SDL_Quit();
    }

    void environment::render() {
        tick++;

        // Clear screen (background color).
//        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Dark grey.
//        SDL_RenderClear(renderer);

        SDL_GL_SetSwapInterval(1);

        /* Clear our buffer with a red background */
        glClearColor ( 0.0, 0.0, 0.0, .3 );
        glClear ( GL_COLOR_BUFFER_BIT );

        glBegin( GL_LINE_LOOP );
        for(double i = 0; i < 2 * PI * radius; i += PI / 50) //<-- Change this Value
            glVertex2d(cos(i) * radius, sin(i) * radius);
        glEnd();

        //////

        double unit = PI / 50;
        double dx = tick * unit;
        double dy = tick * unit;

        //////
        double arc_size = (2 * PI * radius) / 10;
        unsigned int edge_points = (unsigned int) floor(arc_size / unit);

//        glBegin( GL_POINTS );
//        for(int i = 0; i <= edge_points; i++) {
//            double theta = PI - (unit*i);
//            glVertex2d(cos(theta) * (radius - 0.01), sin(theta) * (radius - 0.01));
//        }
//
//        for(int i = edge_points; i >= 0; i--) {
//            double theta = PI - (unit*i);
//            glVertex2d(cos(theta) * (radius - 0.03), sin(theta) * (radius - 0.03));
//        }
//        glEnd();

        glBegin( GL_TRIANGLE_STRIP );
        for(int i = 0; i <= 2*edge_points + 1; i++) {
            double theta = PI - (unit * (i >> 1)) + dx;

            if (i % 2 == 0)
                glVertex2d(cos(theta) * (radius - 0.01), sin(theta) * (radius - 0.01));
            else
                glVertex2d(cos(theta) * (radius - 0.03), sin(theta) * (radius - 0.03));
        }
        glEnd();


        /* Swap our back buffer to the front */
        SDL_GL_SwapWindow(window);

        // Swap buffers.
        //SDL_RenderPresent(renderer);
    }

    void environment::frame_delay() {
        SDL_Delay(25);
    }

    bool environment::get_event() {
        // Handle events.
        SDL_Event event {};
        while (SDL_PollEvent(&event)) {
            // Track mouse movement.
//            if (event.type == SDL_MOUSEMOTION) {
//                SDL_GetMouseState(&mouse_x, &mouse_y);
//            }

            // Clicking 'x' or pressing F4.
            if (event.type == SDL_QUIT) {
                return true;
            }

//            // Joystick direction controller moved.
//            if (event.type == SDL_JOYAXISMOTION) {
//                // 32767.
//                // Up or down.
//                if (event.jaxis.axis == 1) {
//                    gamepad_direction = event.jaxis.value/5461;
//                }
//            }

            // Joystick action button pressed.
//            if (event.type == SDL_JOYBUTTONDOWN) {
//                if (ball->status == ball->READY) {
//                    ball->status = ball->LAUNCH;
//                }
//            }

            // Pressing a key.
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    // Pressing ESC exits from the game.
                    case SDLK_ESCAPE:
                        return true;

                        // Pressing space will launch the ball if it isn't
                        // already launched.
                    case SDLK_SPACE:
//                        if (ball->status == ball->READY) {
//                            ball->status = ball->LAUNCH;
//                        }
                        break;


                        // Pressing F11 to toggle fullscreen.
//                    case SDLK_F11:
//                        int flags = SDL_GetWindowFlags(window);
//                        if (flags & SDL_WINDOW_FULLSCREEN) {
//                            SDL_SetWindowFullscreen(window, 0);
//                        } else {
//                            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
//                        }
//                        break;
                    default:
                        break;
                }
            }
        }

        return false;
    }
}
