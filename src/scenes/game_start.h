//
// Created by Avikam Agur on 15/12/2017.
//

#ifndef CIRPONG_GAME_START_H
#define CIRPONG_GAME_START_H

#include <glm/glm.hpp>
#include <vector>
#include <functional>

#include "src/state.h"
#include "src/config.h"
#include "src/scenes/text_drawer.h"

namespace pong {
    class game_start {
        using text_factory = std::function<std::string(const state&)>;
        using text_positions_t = std::tuple<
                text_factory,
                glm::mat4
        >;
        enum class texts_idx : std::size_t {
            counter = 0,
            start_game,
            push,
            to,
            start,
            two_player,
            push_to_start,
            instruction,
            instruction1,
            instruction2,
            instruction4,
            play,
            paused,
            win1,
            win2,
            score1,
            score2,
            end
        };

        text_drawer &_txt_drawer;
        const config& _conf;

        std::vector<text_positions_t> texts;


        GLuint shaderProgram;

        GLuint vao;
        GLuint vbo;
        GLuint ebo[1];

        GLuint textures[static_cast<size_t>(texts_idx::end)];

        void draw_text_in_texture(int tex_num, const std::string &s);

        template<std::size_t... I>
        void _render_text(std::index_sequence<I...>);

    public:
        explicit game_start(const config& conf, text_drawer &txt_drawer);
        ~game_start();

        void render(pong::state &s);
        void invalidate(const pong::state &s);
    };
}


#endif //CIRPONG_GAME_START_H
