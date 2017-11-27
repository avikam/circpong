//
// Created by Avikam Agur on 11/11/2017.
//

#ifndef CIRPONG_CONSTANTS_H
#define CIRPONG_CONSTANTS_H

namespace pong {
    namespace constants {
        // arena radius
        static double radius = 1;
        static double PI = 3.1415926535897932384626433832795;
        static double arc_size = (2 * PI * radius) / 10;

        // TODO: Consider calculating by player speed or other player position
        static int collision_cooldown_max_val = 10;

        static int screen_width = 640;
        static int screen_height = 640;

        static float player_size = 0.03;
        constexpr unsigned player_pixel_levels = 2;

        static float hit_threshold = 0.005;
    }
}

#endif //CIRPONG_CONSTANTS_H
