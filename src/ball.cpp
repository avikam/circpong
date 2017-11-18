//
// Created by Avikam Agur on 11/11/2017.
//

#include "src/ball.h"
#include <cmath>
#include <iostream>
#include <random>

#define PI 3.14159265

std::random_device rd;     // only used once to initialise (seed) engine
std::mt19937_64 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
std::uniform_int_distribution<int> uni(-50,50); // guaranteed unbiased

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
        auto theta_factor = p.collision_with_ball(x_, y_);
        auto Angle_shift = uni(rng);
        float shift_cos;
        float shift_sin;
        if (theta_factor != -2) {
            if (theta_factor >= 0) {
                speed_x += theta_factor / 1000;
            }
            else
                speed_y += theta_factor/1000;

            speed_x *= -1;
            speed_y *= -1;
            // rotate speed vector by random angle
            shift_cos = cos(Angle_shift*PI/180);
            shift_sin = sin(Angle_shift*PI/180);

            auto speed_x_tmp = speed_x*shift_cos - speed_y*shift_sin;
            speed_y = speed_x*shift_sin + speed_y*shift_cos;
            speed_x = speed_x_tmp;

            // theta_ += theta_factor * (constants::PI) / 4;
            return true;
        }

        return false;
    }

    bool ball::outside_arena() {
        std::cout << x_ << ", " << y_ << std::endl;
        return x_ * x_ + y_ * y_ >= (constants::radius - 0.51) * (constants::radius - 0.51);
    }


}