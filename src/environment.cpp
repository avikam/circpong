//
// Created by Avikam Agur on 10/11/2017.
//

#include <SDL2/SDL_opengl.h>
#include <iostream>
#include "src/constants.h"
#include "src/environment.h"

namespace pong{
    input_t environment::get_event() {
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
                return input_t::quit;
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
                        return input_t::quit;

                        // Pressing space will launch the ball if it isn't
                        // already launched.
                    case SDLK_SPACE:
                        return input_t::pause;

                    case SDLK_UP:
                        return input_t::player_1_up;
                    case SDLK_DOWN:
                        return input_t::player_1_down;
                    case SDLK_q:
                        return input_t::player_2_down;
                    case SDLK_a:
                        return input_t::player_2_up;

//                    case SDLK_t:
//                        b.move_(0.01, 0);
//                        break;
//                    case SDLK_g:
//                        b.move_(-0.01, 0);
//                        break;
//                    case SDLK_h:
//                        b.move_(0, 0.01);
//                        break;
//                    case SDLK_f:
//                        b.move_(0, -0.01);
//                        break;

                    case SDLK_z:
                        break;
                    default:
                        break;
                }
            }
        }
        return input_t::idle;
    }
}
