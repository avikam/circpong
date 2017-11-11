//
// Created by Avikam Agur on 11/11/2017.
//

#include "src/player.h"

namespace pong {
    player::player(double origin, bool direction_up, double unit) :
            origin_ {origin},
            unit_ {direction_up ? unit : -1 * unit}
    {}

    double player::get_origin() {
        return origin_;
    }

    void player::go_up() {
        origin_ += unit_;
    }
    void player::go_down() {
        origin_ -= unit_;
    }
}