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
            edge_points { 3 },
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

    float player::collision_with_ball(double ball_x, double ball_y) const {
        int min_i = -1;
        double min_dist = 1000;


//        double height = 0.03;
//        double width = 0.03;
//        double o = origin_;
//
//        rot = (o , 0, 0, 1);
//        trans = (constants::radius - (edge_points + 1) * width, 0, 0);
//
//        for(int i = 0; i < 2*edge_points + 1; i++) {
//            double point_x = (i >> 1) * height * 0.5;
//            double point_y = width*((1 - 2*(i & 1)) * (edge_points - (i>>1)));
//
//            auto dist = pow(point_x - ball_x, 2) + pow(point_y - ball_y, 2);
//            if (dist < min_dist) {
//                min_dist = dist;
//                min_i = i;
//            }
//        }
//
//        int mid = (edge_points >> 1);
//        float d = (min_i - mid);
//
//        std::cout << "hit " << min_i << ", dist: " << min_dist << ", factor: " << fabsf(d) << std::endl;
//        if (min_dist <= 0.005) {
//            return d / mid;
//        }

        return -1;
    }
}