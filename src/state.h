//
// Created by Avikam Agur on 25/11/2017.
//

#ifndef CIRPONG_STATE_H
#define CIRPONG_STATE_H

#include "src/constants.h"
#include "src/environment.h"
#include "src/player.h"
#include <vector>
#include <tuple>

namespace pong {
    struct state {
        bool is_paused;

        float ball_speed_x;
        float ball_speed_y;
        pos_t ball_pos;

        player p1;
        player p2;

        // After detecting a collision we start this timer that is reduced every frame
        // in which collision detection is disabled so we won't have "collision loop"
        int collision_cooldown;

        state() :
            is_paused { true  },
            p1(0),
            p2(180),

            ball_speed_x {0.01},
            ball_speed_y {0.01},
            ball_pos {0, 0},

            collision_cooldown { constants::collision_cooldown_max_val }
            {};

        void update(input_t);

        bool is_ball_player_collision(const player_pos_t &p);

        /*
         * return nullptr if no goal occurred or player scored the goal.
         */
        int test_goal();
    };
}

#endif //CIRPONG_STATE_H
