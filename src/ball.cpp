//
// Created by Avikam Agur on 11/11/2017.
//

#include "src/ball.h"
#include <cmath>
#include <iostream>

namespace pong {
    ball::ball(double speed) : speed_x {speed}, speed_y { speed }, x_ {0}, y_ {0} {}

    void ball::move() {
        x_ += speed_x;
        y_ += speed_y;
    }

    void ball::get_location(double *x, double* y) const{
        *x = x_;
        *y = y_;
    }

    bool ball::hit_if_collided(const player &p) {
        auto theta_factor = p.collision_from_center(x_, y_);

        if (theta_factor != -1) {
            if (theta_factor >= 0)
                speed_x += theta_factor/1000;
            else
                speed_y += theta_factor/1000;

            speed_x *= -1;
            speed_y *= -1;
            // theta_ += theta_factor * (constants::PI) / 4;
            return true;
        }

        return false;
    }

    bool ball::outside_arean() {
        return x_ * x_ + y_ * y_ >= (constants::radius - 0.055) * (constants::radius - 0.055);
    }


}