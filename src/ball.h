//
// Created by Avikam Agur on 11/11/2017.
//

#ifndef CIRPONG_BALL_H
#define CIRPONG_BALL_H

#include "src/constants.h"
#include "src/player.h"

namespace pong {
    class ball {
        // distance from origin
        double distance;
        // angle of linear movement
        double theta_;

        double speed_;
    public:
        ball(double theta = constants::PI, double speed = 0.01);

        //bool collide_with(const player& p);
        void move();

        void get_location(double* dist, double* theta) const;
        //bool collide_with();
    };
}


#endif //CIRPONG_BALL_H
