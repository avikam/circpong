//
// Created by avikam on 18/11/17.
//

#include <SDL2/SDL_events.h>
#include <iostream>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>

#include "src/control.h"

#define dev "/dev/input/powermate"

namespace pong {
    PowermateControl::PowermateControl() {
        devfd = open(dev, O_RDWR);
        if (devfd == -1) {
            fprintf(stderr, "Could not open %s: %s\n", dev, strerror(errno));
            sleep(1);
        }

        nfds = 1;
        timeout = 10;
        pfds = new struct pollfd[nfds + 1];

        // add devfd
        pfds[1].fd = devfd;
        pfds[1].events = POLLIN;
        pfds[1].revents = 0;

    }

    void PowermateControl::poll_event() {
        int ret = poll(pfds, nfds+1, timeout);
        if (ret < 0) {
            fprintf(stderr, "poll failed\n");
            exit(1);
        }
        auto read_event = pfds[nfds].revents;
        ::input_event ev {};
        while (read_event-- > 0) {
            auto n = read(devfd, &ev, sizeof(ev));
            if (n != sizeof(ev)) {
                printf("Device disappeared!\n");
                devfd = -1;
            }
            else {
                if (ev.type == EV_REL && ev.code == 7) {
                    if (ev.value == -1) {
                        // counter clock-wise turn
                        go_up();
                    }
                    else if (ev.value == 1) {
                        // clock-wise turn
                        go_down();
                    }
                }
                else if (ev.type == EV_KEY && ev.code == 256) {
                    std::cout << "click" << std::endl;
                    if (ev.value == 1) {
                        // knob depressed
                        set_led(0);
                    }
                    else if (ev.value == 0) {
                        // knob released
                    }
                }
            }
        }
    };

    void PowermateControl::go_up() {
        post_key(SDLK_UP);
    }
    void PowermateControl::go_down() {
        post_key(SDLK_DOWN);
    }

    void PowermateControl::post_key(SDL_Keycode key_code) {
        SDL_Event ev{};
        ev.type = SDL_KEYDOWN;
        //ev.key.windowID = win_id;
        ev.key.state = SDL_PRESSED;
        ev.key.keysym.sym = key_code;

        auto ret = SDL_PushEvent(&ev);
    }

    void PowermateControl::set_led(unsigned int val)  {
        ::input_event ev {};
        ev.type = EV_MSC;
        ev.code = MSC_PULSELED;
        ev.value = val;
        if (write(devfd, &ev, sizeof(ev)) != sizeof(ev)) {
            std::cerr << "cant set led " << std::endl;
        }
    }

}