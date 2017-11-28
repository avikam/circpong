//
// Created by Avikam Agur on 27/11/2017.
//

#include "src/state.h"

namespace pong {
    void state::update(input_t event) {
        is_goal = false;

        if (event == input_t::pause) {
            is_paused = !is_paused;
        }

        if (is_paused)
            return;

        if (event == input_t::player_1_up) {
            p1.go_up();
            std::cout << p1.pos[0].first << ", " << p1.pos[0].second << std::endl;

        }
        if (event == input_t::player_1_down) {
            p1.go_down();
            std::cout << p1.pos[0].first << ", " << p1.pos[0].second << std::endl;
        }

        if (event == input_t::player_2_up) {
            p2.go_up();
        }
        if (event == input_t::player_2_down) {
            p2.go_down();
        }


        ball_pos.first  += ball_speed_x;
        ball_pos.second += ball_speed_y;

        if (collision_cooldown > 0) {
            collision_cooldown -= 1;
        } else {
            if (is_ball_player_collision(p1.pos)) {
                std::cout << "player 1 collision";

                collision_cooldown = constants::collision_cooldown_max_val;
                ball_speed_x *= -1;
                ball_speed_y *= -1;
            }

            if (is_ball_player_collision(p2.pos)) {
                std::cout << "player 2 collision";

                collision_cooldown = constants::collision_cooldown_max_val;
                ball_speed_x *= -1;
                ball_speed_y *= -1;
            }
        }

        auto winner = test_goal();
        if (winner != nullptr) {
            is_paused = true;
            is_goal = true;

            ball_speed_x = 0.01;
            ball_speed_y = 0.01;
            ball_pos = {0, 0};

            winner->score += 1;
        }
    }

    bool state::is_ball_player_collision(const player_pos_t &p) {
        double min_dist_sq = 1000;

        for (const auto& pixel : p) {
            auto dist_sq = pow(pixel.first - ball_pos.first, 2) + pow(pixel.second - ball_pos.second, 2);
            if (dist_sq < min_dist_sq) {
                min_dist_sq = dist_sq;
            }
        }

        if (min_dist_sq < constants::hit_threshold) {
            return true;
        }

        return false;
    }

    player* state::test_goal() {
        if (pow(ball_pos.first, 2) + pow(ball_pos.second, 2) <= (0.95*0.95) ) {
            return nullptr;
        }

        // check x coordinate (first coordinate) of the ball being to the left or to the right of the center
        if (ball_pos.first > 0) {
            return &p2;
        }

        return &p1;
    }
}
