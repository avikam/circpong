//
// Created by Avikam Agur on 10/11/2017.
//

#include <SDL2/SDL_opengl.h>
#include <iostream>
#include "src/constants.h"
#include "src/environment.h"

namespace pong{
    static float radius = 1;


    environment::environment() :
            tick {0},
            unit {constants::PI / 50},
            p1 { 0, true, unit},
            p2 { constants::PI, false, unit},
            b { 0.005 },
            state { state_t::active }
    {
    }

    environment::~environment() {
    }


    void environment::render(const ball &b) {

    }

    void environment::renderAndSetCoordinate(player &p) {
    }

    void environment::update() {
        if (state != state_t::active) {
            return;
        }
        
        b.move();

        if (turn_p1) {
            if (b.hit_if_collided(p1)) {
                turn_p1 = !turn_p1;
            }
        } else {
            if (b.hit_if_collided(p2)) {
                turn_p1 = !turn_p1;
            }
        }
    }

    bool environment::get_event() {
        pm_ct.poll_event();
        // Handle events.
        SDL_Event event {};
        while (SDL_PollEvent(&event)) {
            // Track mouse movement.
            if (event.type == SDL_MOUSEMOTION) {
                int mouse_x;
                //SDL_GetMouseState(&mouse_x, &tick);
            }

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
                        state = state_t::user_quit;
                        return true;

                        // Pressing space will launch the ball if it isn't
                        // already launched.
                    case SDLK_SPACE:
//                        if (ball->status == ball->READY) {
//                            ball->status = ball->LAUNCH;
//                        }
                        break;

                    case SDLK_UP:
                        p1.go_up();
                        break;
                    case SDLK_DOWN:
                        p1.go_down();
                        break;

                    case SDLK_q:
                        p2.go_up();
                        break;
                    case SDLK_a:
                        p2.go_down();
                        break;


                    case SDLK_t:
                        b.move_(0.01, 0);
                        break;
                    case SDLK_g:
                        b.move_(-0.01, 0);
                        break;
                    case SDLK_h:
                        b.move_(0, 0.01);
                        break;
                    case SDLK_f:
                        b.move_(0, -0.01);
                        break;

                    case SDLK_z:
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

    bool environment::is_active() {
        return state != state_t::user_quit;
    }
}
