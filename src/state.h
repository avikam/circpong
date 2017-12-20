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
#include <chrono>

using namespace std::chrono;


namespace pong {
    class state {
        /*
         * return nullptr if no goal occurred or player scored the goal.
         */
        player* test_goal();

        bool is_ball_player_collision(float angle);
        void hit();
        std::random_device rd;     // only used once to initialise (seed) engine
        std::mt19937_64 rng;    // random-number engine used (Mersenne-Twister in this case)
        std::uniform_int_distribution<int> uni; // guaranteed unbiased


    public:
        bool is_welcome;
        bool is_instructions;
        bool is_game_start;
        // After a goal
        bool is_paused;
        // User ask for pause
        bool is_player_pressed_paused;
        bool is_goal;
        bool is_game_over;

        float ball_speed_x;
        float ball_speed_y;
        pos_t ball_pos;

        high_resolution_clock::time_point game_start_time;

        player p1;
        player p2;

        player* curr_winner;

        // After detecting a collision we start this timer that is reduced every frame
        // in which collision detection is disabled so we won't have "collision loop"
        int collision_cooldown;

        std::chrono::seconds start_game_count_down;

        state() :
            is_welcome { true },
            is_instructions { false },
            is_game_start { false },
            is_paused { true  },
            is_player_pressed_paused { false },
            is_goal { false },
            is_game_over {false },
            p1("Player 1", 90),
            p2("Player 2", 90+180),
            curr_winner {nullptr},

            ball_speed_x {0.01},
            ball_speed_y {0.01},
            ball_pos {0, 0},

            collision_cooldown { constants::collision_cooldown_max_val },
            rng { rd() },
            uni {-20,20},
            game_start_time { high_resolution_clock::now() },
            start_game_count_down { 0 }
            {};

        void update(input_t);
    };
}

#endif //CIRPONG_STATE_H
