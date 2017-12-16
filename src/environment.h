//
// Created by Avikam Agur on 10/11/2017.
//
#ifndef CIRPONG_INPUT_HANDLER_H
#define CIRPONG_INPUT_HANDLER_H


#include "src/ball.h"
#include "src/player.h"
#include "src/control.h"
#include "src/input.h"
#include <bitset>
#include <utility>


namespace pong {
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
