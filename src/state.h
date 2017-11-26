//
// Created by Avikam Agur on 25/11/2017.
//

#ifndef CIRPONG_STATE_H
#define CIRPONG_STATE_H

#include "src/constants.h"
#include <vector>
#include <tuple>
namespace pong {
    struct state {
        using player_pos_t = std::vector<std::pair<float, float>>;

        bool is_paused;
        int score_1;
        int score_2;

        float player_1_ang;
        float player_2_ang;

        // (x,y) for each center of pixel. there are 2 pixels in every level and 1 as the base.
        player_pos_t player_1_pos_xy;
        player_pos_t player_2_pos_xy;

        state() :
            is_paused { true  },
            score_1 { 0 },
            score_2 { 0 },
            player_1_pos_xy (2 * constants::player_pixel_levels + 1),
            player_2_pos_xy (2 * constants::player_pixel_levels + 1),
            player_1_ang(0),
            player_2_ang(180)
            {};
    };
}

#endif //CIRPONG_STATE_H
