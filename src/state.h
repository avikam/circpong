//
// Created by Avikam Agur on 25/11/2017.
//

#ifndef CIRPONG_STATE_H
#define CIRPONG_STATE_H

#include "src/constants.h"
#include "src/environment.h"
#include <vector>
#include <tuple>

namespace pong {
    struct state {
        using pos_t = std::pair<float, float>;
        using player_pos_t = std::vector<pos_t>;

        bool is_paused;
        int score_1;
        int score_2;

        float player_1_ang;
        float player_2_ang;

        // (x,y) for each center of pixel. there are 2 pixels in every level and 1 as the base.
        player_pos_t player_1_pos_xy;
        player_pos_t player_2_pos_xy;

        float ball_speed_x;
        float ball_speed_y;
        pos_t ball_pos;

        // After detecting a collision we start this timer that is reduced every frame
        // in which collision detection is disabled so we won't have "collision loop"
        int collision_cooldown;

        state() :
            is_paused { true  },
            score_1 { 0 },
            score_2 { 0 },
            player_1_pos_xy (2 * constants::player_pixel_levels + 1),
            player_2_pos_xy (2 * constants::player_pixel_levels + 1),
            player_1_ang(0),
            player_2_ang(180),

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
