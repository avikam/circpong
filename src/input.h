//
// Created by pong on 16/12/17.
//

#ifndef CIRPONG_INPUT_H
#define CIRPONG_INPUT_H

#include <type_traits>

namespace pong {
    enum class input_t : int {
        // no input between frames
        idle                = 0,
        player_1_up         = 0x001,
        player_1_down       = 0x002,
        player_2_up         = 0x004,
        player_2_down       = 0x008,

        toggle_fullscreen   = 0x010,

        p1_press            = 0x100,
        p2_press            = 0x200,
        quit                = 0x400
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

    inline bool input_is_set(const input_t val, const input_t flag) {
        return input_t::idle != (val & flag);
    }

    inline bool input_is_pause(const input_t val) {
        return input_is_set(val, input_t::p1_press | input_t::p2_press);
    }

    inline bool input_all_pressed(const input_t val) {
        return input_is_set(val, input_t::p1_press) && input_is_set(val, input_t::p2_press);
    }
}

#endif //CIRPONG_INPUT_H
