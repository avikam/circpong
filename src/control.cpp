//
// Created by avikam on 18/11/17.
//

#include <SDL2/SDL_events.h>
#include <iostream>
#include <vector>
#include <string>

#include <sys/types.h>
#include <linux/input.h> // struct input_event
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

#include "src/control.h"

namespace pong {
    static bool find_controls(std::vector<std::string>& out_paths) {
        std::string controls_path_str { controls_path };
        auto dirp = opendir(controls_path);
        int found = 0;

        while (true) {
            auto dp = readdir(dirp);
            if (dp == nullptr) {
                break;
            }

            std::string s{dp->d_name};
            if (s != "." && s != "..") {
                if (found++ < max_controls) {
                    out_paths.push_back(controls_path_str + s);
                } else {
                    // to many files found
                    break;
                }
            }
        }

        (void)closedir(dirp);
        return found == max_controls;
    }

    PowermateControl::PowermateControl() {
        std::vector<std::string> controls_paths;
        if (!find_controls(controls_paths)) {
            throw std::runtime_error("Controls must be connected");
        }

        std::cout << "found ok: ";
        std::cout << controls_paths[0] << ", " << controls_paths[1] << std::endl;


        for (int i=0; i<max_controls; i++) {
            devfds[i] = open(controls_paths[i].c_str(), O_RDWR);
            if (devfds[i] == -1) {
                std::cerr << "Could not open " << controls_paths[i] << ", " << strerror(errno) << std::endl;
                throw std::runtime_error("Cannot open control");
            }
        }

        nfds = 3;
        timeout = 10;
        pfds = new struct pollfd[nfds + 1];
    }

    void PowermateControl::poll_event() {
        // add devfd
        for (int i=0; i < max_controls; i++) {
            pfds[1 + i].fd = devfds[i];
            pfds[1 + i].events = POLLIN;
            pfds[1 + i].revents = 0;
        }

        int ret = poll(pfds, nfds+1, timeout);
        if (ret < 0) {
            fprintf(stderr, "poll failed\n");
            exit(1);
        }
        if (ret == 0) {
            return;
        }

        for (int i=1; i<=1 + max_controls; i++) {
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
                            // set_led(pfds[i].fd, 0);
                            post_key(SDLK_SPACE);
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

    void PowermateControl::set_led(int fd_ctrl, unsigned int val)  {
        ::input_event ev {};
        ev.type = EV_MSC;
        ev.code = MSC_PULSELED;
        ev.value = val;
        if (write(fd_ctrl, &ev, sizeof(ev)) != sizeof(ev)) {
            std::cerr << "cant set led " << std::endl;
        }
    }

}
