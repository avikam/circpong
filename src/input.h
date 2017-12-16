//
// Created by pong on 16/12/17.
//

#ifndef CIRPONG_INPUT_H
#define CIRPONG_INPUT_H

#include <type_traits>

namespace pong {
    enum class input_t : int{
        // no input between frames
        idle = 0,
        player_1_up = 0x01,
        player_1_down = 0x02,
        player_2_up = 0x04,
        player_2_down = 0x08,

        toggle_fullscreen = 0x10,

        pause = 0x100,
        quit = 0x1000
    };

    using T = std::underlying_type_t <input_t>;

    inline input_t operator| (input_t lhs, input_t rhs)
    {
        return (input_t)(static_cast<T>(lhs) | static_cast<T>(rhs));
    }

    inline input_t& operator|= (input_t& lhs, input_t rhs)
    {
        lhs = (input_t)(static_cast<T>(lhs) | static_cast<T>(rhs));
        return lhs;
    }

    inline input_t operator& (input_t lhs, input_t rhs)
    {
        return (input_t)(static_cast<T>(lhs) & static_cast<T>(rhs));
    }
}

#endif //CIRPONG_INPUT_H
