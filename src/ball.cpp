//
// Created by Avikam Agur on 11/11/2017.
//

#include "src/ball.h"
namespace pong {
    ball::ball(double theta, double speed) : theta_{theta}, distance {0}, speed_ {speed} {}

    void ball::move() {
        distance += speed_;
    }

    void ball::get_location(double *dist, double* theta) const{
        *dist = distance;
        *theta = theta_;
    }


}