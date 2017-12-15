//
// Created by Avikam Agur on 11/11/2017.
//

#include <cmath>
#include <cstring>
#include <iostream>

#include "src/constants.h"
#include "src/player.h"


namespace pong {
    player::player(std::string name, float angle)  :
        name { std::move(name) },
        angular_speed { 4 },
        angle_ { angle },
        boundaries {angle-85,angle+85},
        score {0},
        pos(2 * constants::player_pixel_levels + 1)
    {}

    void player::go_up() {
        auto new_angle = angle_ + angular_speed;
        if (boundaries.first <= new_angle && new_angle <= boundaries.second)
            angle_ = new_angle;
    }
    void player::go_down() {
        auto new_angle = angle_ - angular_speed;
        if (boundaries.first <= new_angle && new_angle <= boundaries.second)
            angle_ = new_angle;
    }
}