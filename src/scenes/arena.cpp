//
// Created by Avikam Agur on 25/11/2017.
//

#include "src/scenes/arena.h"
#include "src/scenes/utils.h"

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

    static const char* geometricSource = R"glsl(
        #version 150 core

        layout(points) in;
        layout(line_strip, max_vertices = 100) out;

        const float PI = 3.1415926;
        const int SIZE = 50;

        void main()
        {
            for (int i = 0; i <= SIZE; i++) {
                // Angle between each side in radians
                // 2 * PI * r *  (i/SIZE); r = 1
                float ang = 2.0 * PI / SIZE * i;

                // Offset from center of point
                vec4 offset = vec4(0.95 * cos(ang), 0.95 * sin(ang), 0.0, 0.0);
                gl_Position = gl_in[0].gl_Position + offset;

                EmitVertex();
            }

            EndPrimitive();
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

        GLint geometricShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometricShader, 1, &geometricSource, nullptr);
        compile_shader(geometricShader);

        GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
        compile_shader(fragmentShader);

        // Link the vertex and fragment shader into a shader program
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, geometricShader);
        glAttachShader(shaderProgram, fragmentShader);
        glBindFragDataLocation(shaderProgram, 0, "outColor");
        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);

        glGenBuffers(1, &vbo);
        GLfloat vertices[] = {
            //  Position
            0.0f, 0.0f
        };

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


        // Specify the layout of the vertex data
        // must happen AFTER binding vbo, otherwise glDrawArrays seems to be able draw on the account of
        // invalid op
        GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
        // uses currently bound vertex array object for the operation
        glEnableVertexAttribArray(posAttrib);
        glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);

        glDeleteShader(fragmentShader);
        glDeleteShader(geometricShader);
        glDeleteShader(vertexShader);
    }

    void arena::render(pong::state s) {
        glUseProgram(shaderProgram);
        glBindVertexArray(vao);

        /* Clear our buffer with a red background */
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glDrawArrays(GL_POINTS, 0, 1);
//        auto num_lines = 40;
//        glTranslated(0, -1  * radius/num_lines, 0);
//        glBegin( GL_LINES );
//        for (int i = 0; i < num_lines; i++) {
//            glVertex2d(0, radius - (i * 2*radius / num_lines));
//        }
//        glEnd();
//
//        glLoadIdentity();
//        renderAndSetCoordinate(p1);
//
//        glLoadIdentity();
//        renderAndSetCoordinate(p2);
//
//        glLoadIdentity();
//        render(b);

    }

    arena::~arena() {
        glDeleteProgram(shaderProgram);
    }
}
