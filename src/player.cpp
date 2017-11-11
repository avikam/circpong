//
// Created by Avikam Agur on 11/11/2017.
//

#include <cmath>
#include <iostream>

#include "src/constants.h"
#include "src/player.h"

namespace pong {
    player::player(double origin, bool direction_up, double unit) :
            origin_ {origin},
            edge_points {static_cast<unsigned int>(floor(constants::arc_size / std::abs(unit))) },
            unit_ {direction_up ? unit : -1 * unit}
    {}

    double player::get_origin() const{
        return origin_;
    }

    void player::go_up() {
        origin_ += unit_;
    }
    void player::go_down() {
        origin_ -= unit_;
    }

    float player::collision_from_center(double ball_x, double ball_y) const {
        int min_i = -1;
        double min_dist = 1000;

        for(auto i = 1; i < edge_points; i++) {
            double theta = origin_ + fabs(i* unit_);
            double point_x = cos(theta) * (constants::radius - 0.01);
            double point_y = sin(theta) * (constants::radius - 0.01);

            auto dist = pow(point_x - ball_x, 2) + pow(point_y - ball_y, 2);
            if (dist < min_dist) {
                min_dist = dist;
                min_i = i;
            }
        }

        int mid = (edge_points >> 1);
        float d = (min_i - mid);

        std::cout << "hit " << min_i << ", dist: " << min_dist << ", factor: " << fabsf(d) << std::endl;
        if (min_dist <= 0.005) {
            return d / mid;
        }

        return -1;
    }
}