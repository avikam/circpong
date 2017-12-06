//
// Created by avikam on 18/11/17.
//

#include <SDL2/SDL_events.h>
#include <poll.h> // struct pollfd
#include <iostream>

// Thit constant is from udev rule, don't change!
#define controls_path "/dev/input/powermate/"
#define max_controls 2

namespace pong {
    class PowermateControl {
        unsigned long nfds;
        int timeout;
        struct pollfd *pfds;
        int devfds[max_controls];

        void set_led(int fd, unsigned int val);

        void go_up1();
        void go_down1();

        void go_up2();
        void go_down2();
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