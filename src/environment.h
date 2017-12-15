//
// Created by Avikam Agur on 10/11/2017.
//
#ifndef CIRPONG_INPUT_HANDLER_H
#define CIRPONG_INPUT_HANDLER_H


#include "src/ball.h"
#include "src/player.h"
#include "src/control.h"
#include <bitset>
#include <utility>

namespace pong {
    enum class input_t {
        // no input between frames
        idle = 0,

        player_1_up,
        player_1_down,
        player_2_up,
        player_2_down,

        toggle_fullscreen,

        pause,
        quit,
        last_input
    };

    constexpr auto num_inputs = static_cast<long unsigned int>(input_t::last_input);
    using input_idx_t = std::make_index_sequence<num_inputs>;

//    input_idx_t input_idx{};

//    template <std::size_t... I>
//    struct _inputs{
//        static constexpr std::bitset<num_inputs> inputs[] = {
//                (1<<Ts{}),...
//        };
//    };

    

    /*
     * Input handler - reads from controls and SDLs events.
     */
    class environment {
        PowermateControl pm_ct;

    public:
        input_t get_event();
    };
}

#endif //CIRPONG_INPUT_HANDLER
