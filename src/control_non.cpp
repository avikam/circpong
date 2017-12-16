//
// Created by avikam on 18/11/17.
//

#include "src/control.h"

namespace pong {
    PowermateControl::PowermateControl() {
    }

    input_t PowermateControl::poll_event() {
        return input_t::idle;
    };

}