//
// Created by Avikam Agur on 10/11/2017.
//
#ifndef CIRPONG_INPUT_HANDLER_H
#define CIRPONG_INPUT_HANDLER_H


#include "src/ball.h"
#include "src/player.h"
#include "src/control.h"

namespace pong {
    enum class input_t {
        // no input between frames
        idle,

        player_1_up,
        player_1_down,
        player_2_up,
        player_2_down,

        toggle_fullscreen,

        pause,
        quit
    };

    /*
     * Input handler - reads from controls and SDLs events.
     */
    class environment {
        PowermateControl pm_ct;

    public:
        input_t get_event();
    };
}

#endif //CIRPONG_INPUT_HANDLER
