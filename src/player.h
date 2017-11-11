//
// Created by Avikam Agur on 11/11/2017.
//

#ifndef CIRPONG_PLAYER_H
#define CIRPONG_PLAYER_H

namespace pong {
    class player {
        double origin_;
        double unit_;
        unsigned int edge_points;

    public:
        player(double origin, bool direction_up, double unit);
        void go_up();
        void go_down();
        double get_origin() const;
        float collision_from_center(double distance, double theta) const;
    };
}

#endif //CIRPONG_PLAYER_H
