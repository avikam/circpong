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

        ball_pos.first  += ball_speed_x;
        ball_pos.second += ball_speed_y;
    }
}
