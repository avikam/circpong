//
// Created by Avikam Agur on 11/11/2017.
//

#ifndef CIRPONG_BALL_H
#define CIRPONG_BALL_H

#include "src/constants.h"
#include "src/player.h"

namespace pong {
    class ball {
        double x_;
        double y_;

        double speed_x;
        double speed_y;
    public:
        explicit ball(double speed = 0.01);

        bool outside_arean();
        bool hit_if_collided(const player &p);
        void move();

        void get_location(double* x, double* y) const;
    };
}


#endif //CIRPONG_BALL_H
