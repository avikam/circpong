//
// Created by Avikam Agur on 20/11/2017.
//

#include <OpenGL/gl3.h>
#include "src/text_drawer.h"

#define FONT_PATH "resources/fonts/NES-Chimera/NES-Chimera.ttf"

namespace pong {

    text_drawer::text_drawer() :
            textColor { 255, 255, 255, 255 }, // white
            backgroundColor { 0, 0, 0, 255 } // black
    {
        TTF_Init();
        // Load our fonts, with a huge size
        font = TTF_OpenFont( FONT_PATH, 16 );
        if (font == nullptr) {
            throw std::runtime_error("Can't open fond");
        }
    }

    text_drawer::~text_drawer() {
        TTF_CloseFont(font);
        TTF_Quit();
    }

    void text_drawer::draw(const std::string& str) {
        auto txt = TTF_RenderText_Blended( font, str.c_str(), textColor );

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, txt->w, txt->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, txt->pixels);

        SDL_FreeSurface(txt);
    }
}
