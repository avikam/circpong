//
// Created by Avikam Agur on 27/11/2017.
//

#include "src/state.h"

namespace pong {
    void state::update(input_t event) {
        auto now = high_resolution_clock::now();
        if (event != input_t::idle)
            last_input_time = now;
        else {
            if (duration_cast<seconds>(now - last_input_time).count() > constants::max_seconds_idle) {
                last_input_time = now;

                is_welcome = true;
                is_instructions = false;
                is_paused = true;
                is_game_start = false;

                curr_winner = nullptr;
                p1.score = 0;
                p2.score = 0;
                p1.angle_ = 90;
                p2.angle_ = 90+180;
            }
        }


        is_goal = false;

        if (is_welcome) {
            if (input_is_pause(event)) {
                is_welcome = false;
                is_instructions = true;
                is_paused = true;
                is_game_start = false;
            }

            return;
        }

        if (is_instructions) {
            if (event == input_t::idle) {
                if (duration_cast<seconds>(now - last_input_time).count() > constants::max_seconds_idle_instruction) {
                    is_welcome = true;
                    is_instructions = false;
                    is_paused = true;
                    is_game_start = false;
                }
            } else if (input_is_pause(event)) {
                is_welcome = false;
                is_instructions = false;
                is_paused = true;
                is_game_start = true;
                game_start_time = high_resolution_clock::now();
            }

            return;
        }


        if (is_game_start) {
            start_game_count_down = duration_cast<seconds>(now - game_start_time );
            if (start_game_count_down.count() >= constants::start_game_counter) {
                is_game_start = false;
                is_paused = false;
            } else {
                return;
            }
        }

        if (input_is_pause(event)) {
            // If the game wasn't paused and a pause input has come -> player pressed pause is true to indicate
            // that a "RESUME" statement should be displayed.
            is_player_pressed_paused = !is_paused;

            is_paused = !is_paused;
        }

        if (is_paused)
            return;

        if (is_game_over) {
            is_game_over = false;
            p1.score = 0;
            p2.score = 0;
            curr_winner = nullptr;

            p1.angle_ = 90;
            p2.angle_ = 90+180;

            is_paused = true;
            is_player_pressed_paused = false;
            is_game_start = false;
            is_welcome = true;
        }

        if (input_is_set(event, input_t::player_1_up)) {
            p1.go_up();
        }
        if (input_is_set(event, input_t::player_1_down)) {
            p1.go_down();
        }

        if (input_is_set(event, input_t::player_2_up)) {
            p2.go_up();
        }
        if (input_is_set(event, input_t::player_2_down)) {
            p2.go_down();
        }

        ball_pos.first  += ball_speed_x;
        ball_pos.second += ball_speed_y;

        if (collision_cooldown > 0) {
            collision_cooldown -= 1;
        } else {
            if (ball_pos.second >= 0 && is_ball_player_collision(p1.angle_)) {
                std::cout << "player 1 collision";
                hit();
            }

            if (ball_pos.second <= 0 &&  is_ball_player_collision(p2.angle_ - 180)) {
                std::cout << "player 2 collision";
                hit();
            }
        }

        auto winner = test_goal();
        if (winner != nullptr) {
            is_paused = true;
            is_player_pressed_paused = false;
            is_goal = true;

            ball_speed_x = 0.01;
            ball_speed_y = 0.01;
            ball_pos = {0, 0};
            collision_cooldown = 0;

            winner->score += 1;

            if (winner->score == constants::max_score) {
                is_game_over = true;
                curr_winner = winner;
            }
        }
    }

    bool state::is_ball_player_collision(float player_theta) {
        auto ball_theta = (atan(ball_pos.second / ball_pos.first ) * 180 / constants::PI);
        if (ball_pos.first * ball_pos.second < 0) {
            ball_theta += 180;
        }

        if (pow(ball_pos.first, 2) + pow(ball_pos.second, 2) >= 0.85*0.85) {
            if (player_theta - 6 <= ball_theta && ball_theta <= player_theta + 6)
                return true;
        }
        return false;
    }

    player* state::test_goal() {
        if (pow(ball_pos.first, 2) + pow(ball_pos.second, 2) <= (0.95*0.95) ) {
            return nullptr;
        }

        // check x coordinate (first coordinate) of the ball being to the left or to the right of the center
        if (ball_pos.second > 0) {
            return &p2;
        }

        return &p1;
    }

    void state::hit() {
        collision_cooldown = constants::collision_cooldown_max_val;

        auto Angle_shift = uni(rng);
        // rotate speed vector by random angle
        float shift_cos = cos(Angle_shift * constants::PI/180);
        float shift_sin = sin(Angle_shift * constants::PI/180);

        // change speed
        ball_speed_y *= 1.05;
        ball_speed_x *= 1.05;

        // change direction
        auto speed_x_tmp = ball_speed_x*shift_cos - ball_speed_y*shift_sin;
        ball_speed_y = -1 * (ball_speed_x*shift_sin + ball_speed_y*shift_cos);
        ball_speed_x = -1 * speed_x_tmp;
    }
}
