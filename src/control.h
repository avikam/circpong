//
// Created by avikam on 18/11/17.
//
#ifndef __CIRPONG_CONTROL_H__
#define __CIRPONG_CONTROL_H__


#include <SDL2/SDL_events.h>
#ifdef __linux__
    #include <poll.h> // struct pollfd
#endif
#include <iostream>

#include "src/input.h"

// Thit constant is from udev rule, don't change!
#define controls_path "/dev/input/powermate/"
#define max_controls 2

#define bottom_path "/dev/input/powermate/B"
#define bottom_fd 0

#define upper_path "/dev/input/powermate/U"
#define upper_fd 1

namespace pong {
    class PowermateControl {
        unsigned long nfds;
        int timeout;
        struct pollfd *pfds;
        int devfds[max_controls];
        void set_led(int fd, unsigned int val);

        bool up_pressed;
        bool down_pressed;

    public:
        PowermateControl();

        input_t poll_event();
    };
}

#endif