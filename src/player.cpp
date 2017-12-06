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
        angular_speed { 2 },
        angle_ { angle },
        score {0},
        pos(2 * constants::player_pixel_levels + 1)
    {}

    void player::go_up() {
        angle_ += angular_speed;
    }
    void player::go_down() {
        angle_ -= angular_speed;
    }
}