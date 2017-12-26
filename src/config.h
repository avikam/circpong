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
        int window_size;
        int window_pos_x;
        int window_pos_y;
        float ball_size;
        float radius;
        float initial_velocity;

        config(
                int max_seconds_idle = constants::max_seconds_idle,
                int max_seconds_idle_instruction = constants::max_seconds_idle,
                int max_score = constants::max_score,
                float ball_size = constants::ball_size,
                float radius = constants::radius,
                float initial_velocity = constants::initial_velocity,
                int window_size = 0,
                int window_pos_x = 0,
                int window_pos_y = 0

        ) :
            max_seconds_idle { max_seconds_idle },
            max_seconds_idle_instruction { max_seconds_idle_instruction },
            max_score{ max_score },
            window_size{ window_size },
            window_pos_x{ window_pos_x },
            window_pos_y{ window_pos_y },
            ball_size{ ball_size },
            radius{ radius},
            initial_velocity { initial_velocity }

                {}
    };

}

#endif //CIRPONG_CONFIG_H
