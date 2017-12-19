//
// Created by Avikam Agur on 25/11/2017.
//

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

#include "src/scenes/arena.h"
#include "src/scenes/utils.h"
#include "src/constants.h"

namespace pong {
    // Vertex shader
    static const char* vertexSource = R"glsl(
        #version 150 core
        in vec2 position;

        void main()
        {
            gl_Position = vec4(position, 0.0, 1.0);
        }
    )glsl";

    // Vertex shader
    static const char* vertexPlayerSource = R"glsl(
        #version 150 core
        in vec2 position;
        uniform mat4 trans;

        void main()
        {
            gl_Position = trans * vec4(position, 0.0, 1.0);
        }
    )glsl";

    static const char* geometricSource = R"glsl(
        #version 150 core

        layout(points) in;
        layout(line_strip, max_vertices = 250) out;

        const float PI = 3.1415926;
        const int SIZE = 50;

        void main()
        {
            // Draw main circle
            for (int i = 0; i <= SIZE; i++) {
                // Angle between each side in radians
                // 2 * PI * r *  (i/SIZE); r = 1
                float ang = 2.0 * PI / SIZE * i;

                // Offset from center of point
                vec4 offset = vec4(0.95 * cos(ang), 0.95 * sin(ang), 0.0, 0.0);

                // gl_Position = gl_in[0].gl_Position + offset;
                gl_Position = gl_in[0].gl_Position + offset;
                EmitVertex();
            }
            EndPrimitive();

            // Draw field separation
            for (int i = -47; i <= 47; i++) {
                gl_Position = gl_in[0].gl_Position + vec4(0.01 * 2 * i, 0, 0, 0);
                EmitVertex();

                gl_Position = gl_in[0].gl_Position + vec4(0.01 * (2 * i+1), 0, 0, 0);
                EmitVertex();

                EndPrimitive();
            }
        }
    )glsl";

    // Fragment shader
    static const char* fragmentSource = R"glsl(
        #version 150 core
        out vec4 outColor;

        void main()
        {
            outColor = vec4(1.0, 1.0, 1.0, 1.0);
        }
    )glsl";

    arena::arena() {
        // Create Vertex Array Object
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // Create and compile shaders
        GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSource, nullptr);
        compile_shader(vertexShader);

        GLint playerVertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(playerVertexShader, 1, &vertexPlayerSource, nullptr);
        compile_shader(playerVertexShader);

        GLint geometricShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometricShader, 1, &geometricSource, nullptr);
        compile_shader(geometricShader);

        GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
        compile_shader(fragmentShader);

        // Link the vertex and fragment shader into a shader program
        arenaShaderProgram = glCreateProgram();
        glAttachShader(arenaShaderProgram, vertexShader);
        glAttachShader(arenaShaderProgram, geometricShader);
        glAttachShader(arenaShaderProgram, fragmentShader);
        glBindFragDataLocation(arenaShaderProgram, 0, "outColor");
        glLinkProgram(arenaShaderProgram);

        ballShaderProgram = glCreateProgram();
        glAttachShader(ballShaderProgram, playerVertexShader);
        glAttachShader(ballShaderProgram, fragmentShader);
        glBindFragDataLocation(ballShaderProgram, 0, "outColor");
        glLinkProgram(ballShaderProgram);

        playerShaderProgram = glCreateProgram();
        glAttachShader(playerShaderProgram, playerVertexShader);
        glAttachShader(playerShaderProgram, fragmentShader);
        glBindFragDataLocation(playerShaderProgram, 0, "outColor");
        glLinkProgram(playerShaderProgram);


        glGenBuffers(3, vbo);

        glUseProgram(arenaShaderProgram);
        GLfloat arena_center[] = {0.0f, 0.0f};
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(arena_center), arena_center, GL_STATIC_DRAW);

        glUseProgram(ballShaderProgram);
        GLfloat ball[] = {
            -constants::ball_size / 2, constants::ball_size / 2,
            constants::ball_size / 2, constants::ball_size / 2,
            constants::ball_size / 2, -constants::ball_size / 2,
            -constants::ball_size / 2, -constants::ball_size / 2
        };
        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(ball), ball, GL_STATIC_DRAW);

        glUseProgram(playerShaderProgram);
        GLfloat player[] = {
                -constants::player_size / 2, constants::player_size / 2,
                constants::player_size / 2, constants::player_size / 2,
                constants::player_size / 2, -constants::player_size / 2,
                -constants::player_size / 2, -constants::player_size / 2
        };
        glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(player), player, GL_STATIC_DRAW);


        glDeleteShader(fragmentShader);
        glDeleteShader(geometricShader);
        glDeleteShader(vertexShader);
        glDeleteShader(playerVertexShader);
    }

    void arena::render(pong::state& s) {
        /* Clear our buffer with a red background */
        glBindVertexArray(vao);

        glUseProgram(arenaShaderProgram);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        {
            // Specify the layout of the vertex data
            // must happen AFTER binding vbo, otherwise glDrawArrays seems to be able draw on the account of invalid op
            GLint posAttrib = glGetAttribLocation(arenaShaderProgram, "position");
            // uses currently bound vertex array object for the operation
            glEnableVertexAttribArray(posAttrib);
            glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
        }
        glDrawArrays(GL_POINTS, 0, 1);

        if (!s.is_player_pressed_paused)
            render_ball(s.ball_pos);

        render_player(s.p1);
        render_player(s.p2);
    }

    void arena::render_ball(pos_t ball_pos) {
        glUseProgram(ballShaderProgram);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

        // Specify the layout of the vertex data
        // must happen AFTER binding vbo, otherwise glDrawArrays seems to be able draw on the account of invalid op
        GLint posAttrib = glGetAttribLocation(ballShaderProgram, "position");
        // uses currently bound vertex array object for the operation
        glEnableVertexAttribArray(posAttrib);
        glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);

        GLint uniTrans = glGetUniformLocation(playerShaderProgram, "trans");
        glm::mat4 pos = glm::translate(glm::mat4 {1.0f},
                glm::vec3(ball_pos.first, ball_pos.second, 0)
        );

        glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(pos));
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }

    void arena::render_player(player &p) {
        glUseProgram(playerShaderProgram);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
        {
            // Specify the layout of the vertex data
            // must happen AFTER binding vbo, otherwise glDrawArrays seems to be able draw on the account of invalid op
            GLint posAttrib = glGetAttribLocation(playerShaderProgram, "position");
            // uses currently bound vertex array object for the operation
            glEnableVertexAttribArray(posAttrib);
            glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
        }

        /*  _
         * |0| _
         *    |2| _
         *     _ |4|
         *  _ |3|
         * |1|
         */

        GLint uniTrans = glGetUniformLocation(playerShaderProgram, "trans");
        glm::mat4 trans { 1 };
        //glm::mat4 trans = glm::rotate(glm::mat4 {1.0f}, glm::radians(p.angle_), glm::vec3(0,0,1));

        // 0.90 is little far of the edge of the arena.
        // TODO: this number should be integrated with the shader's factor (0.95)
        glm::mat4 pos = glm::translate(
                glm::rotate(trans, glm::radians(p.angle_), glm::vec3(0,0,1)),
                glm::vec3(0.90, 0, 0)
        );

        glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(pos));
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        // Level n
        float straightness_factor = 0.25f;
        for (int i=1; i <=constants::player_pixel_levels; i++) {
            {
                // 0.75 is the factor of congruence
                auto t = pos * glm::translate(glm::mat4 {1},
                                              glm::vec3{-i * constants::player_size * straightness_factor, i * constants::player_size, 0});
                glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(t));
                glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            }
            {
                auto t = pos * glm::translate(glm::mat4 {1},
                                        glm::vec3{-i * constants::player_size * straightness_factor, -i * constants::player_size, 0});
                glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(t));
                glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

            }
        }
    }

    arena::~arena() {
        glDeleteProgram(ballShaderProgram);
        glDeleteProgram(arenaShaderProgram);
        // delete vertex buffer
        glDeleteBuffers(3, vbo);
        // delete vertex array data
        glDeleteVertexArrays(1, &vao);
    }
}
