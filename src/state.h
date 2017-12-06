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
#include <random>

namespace pong {
    class state {
        /*
         * return nullptr if no goal occurred or player scored the goal.
         */
        player* test_goal();

        bool is_ball_player_collision(const player_pos_t &p);
        void hit();
        std::random_device rd;     // only used once to initialise (seed) engine
        std::mt19937_64 rng;    // random-number engine used (Mersenne-Twister in this case)
        std::uniform_int_distribution<int> uni; // guaranteed unbiased


    public:
        bool is_paused;
        bool is_goal;
        bool is_game_over;

        float ball_speed_x;
        float ball_speed_y;
        pos_t ball_pos;

        player p1;
        player p2;

        player* curr_winner;

        // After detecting a collision we start this timer that is reduced every frame
        // in which collision detection is disabled so we won't have "collision loop"
        int collision_cooldown;

        state() :
            is_paused { true  },
            is_goal { false },
            is_game_over {false },
            p1("Player 1", 0),
            p2("Player 2", 180),
            curr_winner {nullptr},

            ball_speed_x {0.01},
            ball_speed_y {0.01},
            ball_pos {0, 0},

            collision_cooldown { constants::collision_cooldown_max_val },
            rng { rd() },
            uni {-50,50}
            {};

        void update(input_t);
    };
}

#endif //CIRPONG_STATE_H
