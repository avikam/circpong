//
// Created by Avikam Agur on 10/11/2017.
//

#ifndef CIRPONG_WINDOW_H
#define CIRPONG_WINDOW_H

#include "src/ball.h"
#include "src/player.h"
#include "src/control.h"

namespace pong {
    enum class state_t {
        active,
        user_quit
    };

    class environment {
        int tick;
        double unit;
        void renderAndSetCoordinate(player &p);
        void render(const ball& p);

        bool turn_p1;

        PowermateControl pm_ct;

        state_t state ;
        player p1;
        player p2;
        ball b;

    public:
        environment();
        ~environment();

        bool get_event();
        void update();
        bool is_active();
    };
}

#endif //CIRPONG_WINDOW_H
