//
// Created by Avikam Agur on 15/12/2017.
//

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <utility>
#include <iostream>
#include <vector>
#include <sstream>

#include "src/opengl.h"
#include "src/scenes/game_start.h"
#include "src/scenes/utils.h"

// Shader sources
static const GLchar* vertexSource = R"glsl(
    #version 150 core
    in vec2 position;
    in vec3 color;
    in vec2 texcoord;
    out vec3 Color;
    out vec2 Texcoord;
    uniform mat4 trans;
    void main()
    {
        Color = color;
        Texcoord = texcoord;
        gl_Position = trans * vec4(position, 0.0, 1.0);
    }
)glsl";

static const GLchar* fragmentSource = R"glsl(
    #version 150 core
    in vec3 Color;
    in vec2 Texcoord;
    out vec4 outColor;
    uniform sampler2D tex;
    void main()
    {
        outColor = texture(tex, Texcoord) * vec4(Color, 1);
    }
)glsl";

namespace pong {
    game_start::game_start(const config& conf, text_drawer &txt_drawer) :
        _txt_drawer{txt_drawer},
        _conf { conf },
        texts {
                text_positions_t {
                [](const state& s) -> std::string {
                    std::ostringstream stream;
                    stream << (constants::start_game_counter - s.start_game_count_down.count());
                    return stream.str();
                },
                glm::scale(
                   glm::translate(
                           glm::rotate(glm::mat4{1}, glm::radians(270.0f), glm::vec3(0,0,1)),
                           glm::vec3 { 0.0f, -0.25f, 0 }),
                   glm::vec3 { 0.05f, 0.2f, 0 })
                },

                text_positions_t {
                [](const state& s) -> std::string { return "START GAME"; },
                glm::scale(
                        glm::rotate(glm::mat4{1}, glm::radians(270.0f), glm::vec3(0,0,1)),
                        glm::vec3 { .55f, .25f, 0 })
                },

                text_positions_t {
                [](const state& s) -> std::string { return "PUSH"; },
                glm::scale(
                        glm::translate(
                                glm::rotate(glm::mat4{1}, glm::radians(270.0f), glm::vec3(0,0,1)),
                                glm::vec3 {.0f, 0.4f, 0 }),
                        glm::vec3 { .44f, .23f, 0 })
                },
                text_positions_t {
                [](const state& s) -> std::string { return "TO"; },
                glm::scale(
                        glm::translate(
                                glm::rotate(glm::mat4{1}, glm::radians(270.0f), glm::vec3(0,0,1)),
                                glm::vec3 {.0f, 0.0f, 0 }),
                        glm::vec3 { .22f, .23f, 0 })
                },
                text_positions_t {
                [](const state& s) -> std::string { return "START"; },
                glm::scale(
                        glm::translate(
                                glm::rotate(glm::mat4{1}, glm::radians(270.0f), glm::vec3(0,0,1)),
                                glm::vec3 {.0f, -0.4f, 0 }),
                        glm::vec3 { .55f, .23f, 0 })
                },

                text_positions_t {
                [](const state& s) -> std::string { return "2 PLAYER"; },
                glm::scale(
                        glm::translate(
                                glm::rotate(glm::mat4{1}, glm::radians(270.0f), glm::vec3(0,0,1)),
                                glm::vec3 {.0f, 0.0f, 0 }),
                        glm::vec3 { .25f, .08f, 0 })
                },

                text_positions_t {
                [](const state& s) -> std::string { return "PUSH DIAL TO START"; },
                glm::scale(
                        glm::translate(
                                glm::rotate(glm::mat4{1}, glm::radians(270.0f), glm::vec3(0,0,1)),
                                glm::vec3 {.0f, -0.20f, 0 }),
                        glm::vec3 {.56f, .08f, 0 })
                },

                text_positions_t {
                [](const state& s) -> std::string { return "INSTRUCTIONS"; },
                glm::scale(
                        glm::translate(
                                glm::rotate(glm::mat4{1}, glm::radians(270.0f), glm::vec3(0,0,1)),
                                glm::vec3 {.0f, 0.20f, 0 }),
                        glm::vec3 { .45f, .15f, 0 })
                },

                text_positions_t {
                [](const state& s) -> std::string { return "TURN DIAL LEFT OR RIGHT TO CONTROL PADDLE"; },
                glm::scale(
                        glm::translate(
                                glm::rotate(glm::mat4{1}, glm::radians(270.0f), glm::vec3(0,0,1)),
                                glm::vec3 {.0f, 0.0f, 0 }),
                        glm::vec3 { .60f, .07f, 0 })
                },

                text_positions_t {
                [](const state& s) -> std::string { return "PUSH DIAL TO PAUSE GAME"; },
                glm::scale(
                        glm::translate(
                                glm::rotate(glm::mat4{1}, glm::radians(270.0f), glm::vec3(0,0,1)),

                                glm::vec3 {0, -.17f, 0 }),
                        glm::vec3 { .48f, .07f, 0 })
                },

                text_positions_t {
                [this](const state& s) -> std::string {
                    std::ostringstream stream;
                    stream << "FIRST PLAYER TO " << _conf.max_score << " POINTS WINS";
                    return stream.str();
                },
                glm::scale(
                        glm::translate(
                                glm::rotate(glm::mat4{1}, glm::radians(270.0f), glm::vec3(0,0,1)),
                                glm::vec3 {0, -.35f, 0 }),
                        glm::vec3 { .65f, .07f, 0 })
                },

                text_positions_t {
                [](const state& s) -> std::string { return "PUSH DIAL TO PLAY"; },
                glm::scale(
                        glm::translate(
                                glm::rotate(glm::mat4{1}, glm::radians(270.0f), glm::vec3(0,0,1)),
                                glm::vec3 {.0f, -0.65f, 0 }),
                        glm::vec3 { .45f, .1f, 0 })
                },

                text_positions_t {
                        [](const state& s) -> std::string { return "PAUSED"; },
                        glm::scale(
                                glm::rotate(glm::mat4{1}, glm::radians(270.0f), glm::vec3 { .0f,.0f,1.0f }),
                                glm::vec3 { 0.3f, 0.125f, 0 })
                },

                text_positions_t {
                        [](const state& s) -> std::string { return "WIN"; },
                        glm::rotate(
                                glm::scale(glm::translate(glm::mat4{1},glm::vec3 {0.0, 0.5, 0}),
                                           glm::vec3 {0.35f, 0.1f, 0}),
                                glm::radians(180.0f), glm::vec3 {0, 0, 1})
                },

                text_positions_t {
                        [](const state& s) -> std::string { return "WIN"; },
                        glm::rotate(
                                glm::scale(glm::translate(glm::mat4{1}, glm::vec3 {0.0, 0.5 * -1, 0}),
                                           glm::vec3 {0.35f, 0.1f, 0}),
                                glm::radians(180.0f) * 0, glm::vec3 {0, 0, 1})
                },

                // score 1
                text_positions_t {
                        [](const state& s) -> std::string {
                            std::ostringstream stream; stream << s.p1.score; return stream.str();
                },
                glm::scale(
                                glm::rotate(
                                        glm::translate(glm::mat4{1}, glm::vec3 { conf.radius * 0.8f, 0.1f, 0 }),
                                        glm::radians(270.0f), glm::vec3 { .0f,.0f,1.0f }),
                                glm::vec3 { 0.5 * 0.125f, 0.5 * 0.125f, 0 })
                },

                // score 2
                text_positions_t {
                        [](const state& s) -> std::string {
                            std::ostringstream stream; stream << s.p2.score; return stream.str();
                        },
                        glm::scale(
                                glm::rotate(
                                        glm::translate(glm::mat4{1}, glm::vec3 { conf.radius * 0.8f, -0.1f, 0 }),
                                        glm::radians(270.0f), glm::vec3 { .0f,.0f,1.0f }),
                                glm::vec3 { 0.5 * 0.125f, 0.5 * 0.125f, 0 })
                },
        }

    {
        // Create Vertex Array Object
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // Create and compile the vertex shader
        auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSource, nullptr);
        compile_shader(vertexShader);

        // Create and compile the fragment shader
        auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
        compile_shader(fragmentShader);

        // Link the vertex and fragment shader into a shader program
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glBindFragDataLocation(shaderProgram, 0, "outColor");
        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);

        glGenBuffers(1, &vbo);

        GLfloat vertices[] = {
                //  Position      Color             Texcoords
                // Game Over
                -1.0f,   1.0f,     1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // Top-left
                1.0f,  1.0f,     1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // Top-right
                1.0f,  0.0f,     1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
                -1.0f,   0.0f,     1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
        };

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Create an element array
        glGenBuffers(1, ebo);

        GLuint elements[] = {
                0, 1, 2,
                2, 3, 0
        };

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

        glGenTextures(texts.size(), textures);

        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);

    }

    game_start::~game_start() {
        glDeleteTextures(texts.size(), textures);

        glDeleteProgram(shaderProgram);
        // delete elements buffer
        glDeleteBuffers(1, ebo);
        // delete vertex buffer
        glDeleteBuffers(1, &vbo);
        // delete vertex array data
        glDeleteVertexArrays(1, &vao);
    }

    void game_start::draw_text_in_texture(int tex_num, const std::string& s) {

        glActiveTexture(GL_TEXTURE0 + tex_num);
        glBindTexture(GL_TEXTURE_2D, textures[tex_num]);
        _txt_drawer.draw(s);

        //Set Some basic parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    void game_start::invalidate(const pong::state &s) {
        for (int i = 0; i < texts.size(); i++) {
            draw_text_in_texture(i, std::get<0>(texts[i])(s));
        }
    }

    void game_start::render(pong::state &s) {
        glBindVertexArray(vao);
        glUseProgram(shaderProgram);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        // Specify the layout of the vertex data
        // must happen AFTER binding vbo, otherwise glDrawArrays seems to be able draw on the account of
        // invalid op
        GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
        // uses currently bound vertex array object for the operation
        glEnableVertexAttribArray(posAttrib);
        glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), nullptr);

        GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
        glEnableVertexAttribArray(colAttrib);
        glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void *) (2 * sizeof(GLfloat)));

        GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
        glEnableVertexAttribArray(texAttrib);
        glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void *) (5 * sizeof(GLfloat)));

        //Set Blending
        //Required so that the alpha channels show up from the surface
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if (!(s.is_welcome || s.is_game_start || s.is_instructions))
            _render_text(std::index_sequence<size_t(texts_idx::score1), size_t(texts_idx::score2)>{});
        if (s.is_welcome)
            _render_text(std::index_sequence<
                    size_t(texts_idx::push),
                    size_t(texts_idx::to),
                    size_t(texts_idx::start)
            >{});
        if (s.is_instructions)
            _render_text(std::index_sequence<
                    size_t(texts_idx::instruction),
                    size_t(texts_idx::instruction1),
                    size_t(texts_idx::instruction2),
                    size_t(texts_idx::instruction4),
                    size_t(texts_idx::play)
            >{});
        else if (s.is_game_start)
            _render_text(std::index_sequence<size_t(texts_idx::counter), size_t(texts_idx::start_game)>{});
        else if (s.is_player_pressed_paused)
            _render_text(std::index_sequence<size_t(texts_idx::paused)>{});
        else if (s.is_game_over) {
            if (s.curr_winner == &s.p1)
                _render_text(std::index_sequence<size_t(texts_idx::win1)>{});
            else
                _render_text(std::index_sequence<size_t(texts_idx::win2)>{});
        }
        else {
            //throw std::runtime_error("No reason to rander this scene"); // shouldnt be here
        }
    }


    template<std::size_t... I>
    void game_start::_render_text(std::index_sequence<I...>) {
        GLint uniTex = glGetUniformLocation(shaderProgram, "tex");
        GLint uniTrans = glGetUniformLocation(shaderProgram, "trans");

        (void) std::initializer_list<int>{(
            // set texture
            glUniform1i(uniTex, I),
            // set transformation
            glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(
                    glm::scale(glm::mat4 { 1 },glm::vec3{_conf.window_ratio ,1, 0}) *
                    glm::translate(glm::mat4{1}, glm::vec3(_conf.game_center_x, _conf.game_center_y, 0)) *
                            std::get<1>(texts[I])
            )),

            // set elements and draw
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]),
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0),

            0
        )...};


    }
}