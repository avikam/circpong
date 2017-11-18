//
// Created by Avikam Agur on 11/11/2017.
//

#include <cmath>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <cstring>

#include "src/constants.h"
#include "src/player.h"

#define odd_sign(n) (1 - 2*( (n) & 1) )

namespace pong {
    player::player(double origin, bool direction_up, double unit) :
            angle_ {origin},
            edge_points { 3 },
            unit_ {direction_up ? unit : -1 * unit},
            width { 0.03 }, height { 0.03 },
            coordinates { 1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 1}
    {}

    double player::get_origin() const{
        return angle_;
    }

    void player::go_up() {
        angle_ += unit_;
    }
    void player::go_down() {
        angle_ -= unit_;
    }

    float player::collision_with_ball(double ball_x, double ball_y) const {
        int min_p = -1;
        double min_dist_sq = 1000;
        double x;
        double y;

        for(int p = 2*edge_points; p >= 0; p--) {
            get_point_x_y(p, &x, &y);

            double old_pos[4] = {x, y, 0, 1};
            double new_pos[4] = {0};
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    new_pos[i] += coordinates[j * 4 + i] * old_pos[j];
                }
            }

            auto dist_square = pow(new_pos[0] - ball_x, 2) + pow(new_pos[1] - ball_y, 2);
            if (dist_square < min_dist_sq) {
                min_dist_sq = dist_square;
                min_p = p;
            }
        }

        if (min_dist_sq <= 0.001) {
            float d = odd_sign(min_p) * (1 - (min_p >> 1) / float(edge_points));
            std::cout << std::fixed << std::setw(11) << std::setprecision(6) <<
                      "hit " << min_p << ", dist: " << min_dist_sq << ", factor: " << fabsf(d) << std::endl;

            return d;
        }

        return -2;
    }

    void player::set_coordinates(const double new_coordinates[]) {
        std::memcpy(coordinates, new_coordinates, sizeof(coordinates));
    }

    void player::get_point_x_y(int point_num, double *x, double *y) const{
        *x = (point_num >> 1) * height * 0.5;
        *y = width*(odd_sign(point_num) * (edge_points - (point_num>>1)));
    }
}