//
// Created by Avikam Agur on 11/11/2017.
//

#ifndef CIRPONG_PLAYER_H
#define CIRPONG_PLAYER_H

namespace pong {
    class player {
        double angle_;
        double width;
        double height;
        double unit_;
        int edge_points;

        double coordinates[4 * 4];

//        double* get_coordinates();

    public:
        player(double origin, bool direction_up, double unit);
        void go_up();
        void go_down();
        double get_origin() const;
        float collision_with_ball(double distance, double theta) const;

        void set_coordinates(const double new_coordinates[]);

        void get_point_x_y(int point_num, double* x, double* y) const;
    };
}

#endif //CIRPONG_PLAYER_H
