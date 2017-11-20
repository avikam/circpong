//
// Created by avikam on 18/11/17.
//

#include <SDL2/SDL_events.h>
#include <poll.h>
// #include <unistd.h>
// #include <linux/input.h>
#include <iostream>

namespace pong {
    class PowermateControl {
        unsigned long nfds;
        int timeout;
        struct pollfd *pfds;
        int devfd;

        void set_led(unsigned int val);

        void go_up();
        void go_down();
        void post_key(SDL_Keycode key_code);

    public:
        PowermateControl();

        enum class EventType {
            GoLeft,
            GoRight,
            PressKnob
        };

        void poll_event();
    };
}