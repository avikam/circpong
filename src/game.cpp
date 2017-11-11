//
// Created by Avikam Agur on 10/11/2017.
//

#include "src/game.h"

namespace pong {

    game::game() :
            env_ {},
            exit_ {false}
    {
    }

    game::~game() {

    }

    void game::play() {
        while (!env_.get_event()) {
            env_.render();
            env_.frame_delay();
        }
    }
}