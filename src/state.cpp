//
// Created by Avikam Agur on 27/11/2017.
//

#include "src/state.h"

namespace pong {
    void state::update(input_t event) {
        if (event == input_t::pause) {
            is_paused = !is_paused;
        }

        if (is_paused)
            return;

        if (event == input_t::player_1_up) {
            player_1_ang+=2;
            std::cout << player_1_pos_xy[0].first << ", " << player_1_pos_xy[0].second << std::endl;

        }
        if (event == input_t::player_1_down) {
            player_1_ang-=2;
            std::cout << player_1_pos_xy[0].first << ", " << player_1_pos_xy[0].second << std::endl;
        }

        if (event == input_t::player_2_up) {
            player_2_ang+=2;
        }
        if (event == input_t::player_2_down) {
            player_2_ang-=2;
        }


        ball_pos.first  += ball_speed_x;
        ball_pos.second += ball_speed_y;

        if (collision_cooldown > 0) {
            collision_cooldown -= 1;
        } else {
            if (ball_player_collision(player_1_pos_xy)) {
                std::cout << "player 1 collision";

                collision_cooldown = constants::collision_cooldown_max_val;
                ball_speed_x *= -1;
                ball_speed_y *= -1;
            }

            if (ball_player_collision(player_2_pos_xy)) {
                std::cout << "player 2 collision";

                collision_cooldown = constants::collision_cooldown_max_val;
                ball_speed_x *= -1;
                ball_speed_y *= -1;
            }
        }
    }

    bool state::ball_player_collision(const player_pos_t& p) {
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
}
