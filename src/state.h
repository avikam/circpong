//
// Created by Avikam Agur on 25/11/2017.
//

#ifndef CIRPONG_STATE_H
#define CIRPONG_STATE_H

namespace pong {
    struct state {
        bool is_paused;
        int score_1;
        int score_2;

        state() :
            is_paused { true  },
            score_1 { 0 },
            score_2 { 0 }
            {};
    };
}

#endif //CIRPONG_STATE_H
