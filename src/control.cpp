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
            int j;
            if (0 == controls_paths[i].compare(0, strlen(bottom_path), bottom_path))
                j = bottom_fd;
            else if (0 == controls_paths[i].compare(0, strlen(upper_path), upper_path))
                j = upper_fd;
            else
                throw std::runtime_error("control not in the correct socket");

            devfds[j] = open(controls_paths[i].c_str(), O_RDWR);
            if (devfds[j] == -1) {
                std::cerr << "Could not open " << controls_paths[i] << ", " << strerror(errno) << std::endl;
                throw std::runtime_error("Cannot open control");
            }
        }

        set_led(devfds[0], 0);
        set_led(devfds[1], 0);

        nfds = 3;
        timeout = 10;
        pfds = new struct pollfd[nfds + 1];
    }

    input_t PowermateControl::poll_event() {
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

        input_t res = input_t::idle;
        if (ret == 0) {
            return res;
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
                            res |= (pfds[i].fd==devfds[bottom_fd] ? input_t::player_1_up : input_t::player_2_up);

                        } else if (ev.value == 1) {
                            // clock-wise turn
                            res |= (pfds[i].fd==devfds[bottom_fd] ? input_t::player_1_down : input_t::player_2_down);
                        }
                    } else if (ev.type == EV_KEY && ev.code == 256) {
                        std::cout << "click" << ev.value << std::endl;
                        if (ev.value == 1) {
                            if (pfds[i].fd==devfds[bottom_fd]) down_pressed = true; else up_pressed = true;
                        } else if (ev.value == 0) {
                            if (pfds[i].fd==devfds[bottom_fd]) down_pressed = false; else up_pressed = false;
                        }

                        if (down_pressed) res |= input_t::p1_press; if (up_pressed) res |= input_t::p2_press;
                    }
                }
            }
        }
        return res;
    };


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
