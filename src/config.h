//
// Created by Avikam Agur on 22/12/2017.
//

#ifndef CIRPONG_CONFIG_H
#define CIRPONG_CONFIG_H

#include <ios>
#include <sstream>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>

#include "src/constants.h"

namespace pong {
    struct config {
        int max_seconds_idle;
        int max_seconds_idle_instruction;
        int max_score;
        int window_size;
        int window_pos_x;
        int window_pos_y;
        float ball_size;
        float radius;
        float game_center_x;
        float game_center_y;
        float initial_velocity;
        float window_ratio;

        config(
                int max_seconds_idle = constants::max_seconds_idle,
                int max_seconds_idle_instruction = constants::max_seconds_idle,
                int max_score = constants::max_score,
                float ball_size = constants::ball_size,
                float radius = constants::radius,
                float game_center_x = 0,
                float game_center_y = 0,
                float initial_velocity = constants::initial_velocity,
                int window_size = 0,
                int window_pos_x = 0,
                int window_pos_y = 0,
                float window_ratio = 9/16


        ) :
            max_seconds_idle { max_seconds_idle },
            max_seconds_idle_instruction { max_seconds_idle_instruction },
            max_score{ max_score },
            window_size{ window_size },
            window_pos_x{ window_pos_x },
            window_pos_y{ window_pos_y },
            ball_size{ ball_size },
            radius{ radius},
            game_center_x{ game_center_x },
            game_center_y{ game_center_y},
            initial_velocity { initial_velocity }

                {}
    };


    static void copy_file(const std::string &to) {
        std::string from =  "." + to + ".tmp";
        std::ifstream ifs(from, std::ios::in | std::ios::binary);
        std::ofstream ofs(to, std::ios::out | std::ios::binary);
        ofs << ifs.rdbuf();
    }

    template <class T>
    static void replace_string(const std::string& config_file, const std::string& key, T value) {
        std::ifstream is(config_file, std::ios::in);
        std::ofstream os("." + config_file + ".tmp", std::ios::out);


        std::ostringstream stringStream;
        // TODO: Needs to make sure newline is in the end of file
        stringStream << key << ".*=.*?\n";
        std::string copyOfStr = stringStream.str();

        std::ostringstream stringStream2;
        stringStream2 << key << " = " << value << std::endl;
        std::string copyOfStr2 = stringStream2.str();

        std::regex rx(copyOfStr);

        std::string str((std::istreambuf_iterator<char>(is)),
                        std::istreambuf_iterator<char>());

        // write the results to an output iterator
        std::regex_replace(std::ostreambuf_iterator<char>(os),
                           str.begin(),
                           str.end(),
                           rx, copyOfStr2);

    }

    template <class T>
    void update_config(const std::string& key, T value) {
        replace_string("config.ini", key, value);
        copy_file("config.ini");
    }
}

#endif //CIRPONG_CONFIG_H
