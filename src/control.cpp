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

#define dev1 "/dev/input/powermate_13"
#define dev2 "/dev/input/powermate_12"

namespace pong {
    PowermateControl::PowermateControl() {
        devfd1 = open(dev1, O_RDWR);
        if (devfd1 == -1) {
            fprintf(stderr, "Could not open %s: %s\n", dev1, strerror(errno));
            sleep(1);
        }
        devfd2 = open(dev2, O_RDWR);
        if (devfd2 == -1) {
            fprintf(stderr, "Could not open %s: %s\n", dev2, strerror(errno));
            sleep(1);
        }

        nfds = 3;
        timeout = 10;
        pfds = new struct pollfd[nfds + 1];
    }

    void PowermateControl::poll_event() {
        // add devfd
        pfds[1].fd = devfd1;
        pfds[1].events = POLLIN;
        pfds[1].revents = 0;

        pfds[2].fd = devfd2;
        pfds[2].events = POLLIN;
        pfds[2].revents = 0;

        int ret = poll(pfds, nfds+1, timeout);
        if (ret < 0) {
            fprintf(stderr, "poll failed\n");
            exit(1);
        }
        if (ret == 0) {
            return;
        }

        for (int i=1; i<=2; i++) {
            if (pfds[i].revents & POLLIN) {
                ::input_event ev{};
                auto n = read(pfds[i].fd, &ev, sizeof(ev));
                if (n != sizeof(ev)) {
                    printf("Device disappeared!\n");
                    throw std::runtime_error("device is out, not supported yet");
                } else {
                    if (ev.type == EV_REL && ev.code == 7) {
                        if (ev.value == -1) {
                            // counter clock-wise turn
                            if (i==1) go_up1(); else go_up2();
                        } else if (ev.value == 1) {
                            // clock-wise turn
                            if (i==1) go_down1(); else go_down2();
                        }
                    } else if (ev.type == EV_KEY && ev.code == 256) {
                        std::cout << "click" << std::endl;
                        if (ev.value == 1) {
                            // knob depressed
                            set_led(0);
                        } else if (ev.value == 0) {
                            // knob released
                        }
                    }
                }
            }
        }
    };

    void PowermateControl::go_up1() {
        post_key(SDLK_UP);
    }
    void PowermateControl::go_down1() {
        post_key(SDLK_DOWN);
    }

    void PowermateControl::go_up2() {
        post_key(SDLK_q);
    }
    void PowermateControl::go_down2() {
        post_key(SDLK_a);
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
        if (write(devfd1, &ev, sizeof(ev)) != sizeof(ev)) {
            std::cerr << "cant set led " << std::endl;
        }
    }

}
