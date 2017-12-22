//
// Created by Avikam Agur on 22/12/2017.
//

#ifndef CIRPONG_CONFIG_H
#define CIRPONG_CONFIG_H

#include "src/constants.h"

namespace pong {
    struct config {
        int max_seconds_idle;
        int max_seconds_idle_instruction;
        int max_score;

        config(
                int max_seconds_idle = constants::max_seconds_idle,
                int max_seconds_idle_instruction = constants::max_seconds_idle,
                int max_score = constants::max_score
        ) :
            max_seconds_idle { max_seconds_idle },
            max_seconds_idle_instruction { max_seconds_idle_instruction },
            max_score{ max_score }
                {}
    };

}

#endif //CIRPONG_CONFIG_H
