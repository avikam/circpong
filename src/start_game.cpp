//
// Created by Avikam Agur on 20/11/2017.
//

#include "src/start_game.h"

#define FONT_PATH "resources/fonts/NES-Chimera/NES-Chimera.ttf"

namespace pong {
    static void render_surface(SDL_Surface* surface) {


    }


//    static void render_surface(SDL_Surface* surface) {
//        auto colors = surface->format->BytesPerPixel;
//        auto texture_format = (colors == 4) ?
//                              (surface->format->Rmask == 0x000000ff ? GL_RGBA : GL_BGRA) : /* alpha */
//                              (surface->format->Rmask == 0x000000ff ? GL_RGB : GL_BGR);    /* no alpha */
//
//        float x = 0;
//        float y = 0;
//
//        glMatrixMode(GL_MODELVIEW);
//        glPushMatrix();
//        glLoadIdentity();
//        glOrtho(0, constants::screen_width, 0, constants::screen_height, -1, 1);
//
//        glMatrixMode(GL_PROJECTION);
//        glPushMatrix();
//        glLoadIdentity();
//        glRotatef(180, 1, 0, 0);
//
//        glDisable(GL_DEPTH_TEST);
//        glEnable(GL_TEXTURE_2D);
//        glEnable(GL_BLEND);
//        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//        GLuint texture;
//        glGenTextures(1, &texture);
//        glBindTexture(GL_TEXTURE_2D, texture);
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0,
//                     GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
//
//        glBegin(GL_QUADS);
//        {
//            glTexCoord2f(0,0); glVertex2f(x, y);
//            glTexCoord2f(1,0); glVertex2f(x + surface->w, y);
//            glTexCoord2f(1,1); glVertex2f(x + surface->w, y + surface->h);
//            glTexCoord2f(0,1); glVertex2f(x, y + surface->h);
//        }
//        glEnd();
//
//        glDisable(GL_BLEND);
//        glDisable(GL_TEXTURE_2D);
//        glEnable(GL_DEPTH_TEST);
//        glDeleteTextures(1, &texture);
//
//        glMatrixMode(GL_PROJECTION);
//        glPopMatrix();
//        glMatrixMode(GL_PROJECTION);
//        glPopMatrix();
//    }

    start_game::start_game(scene** s) : scene_ { s },
            textColor { 255, 255, 255, 255 }, // white
            backgroundColor { 0, 0, 0, 255 } // black
    {
        TTF_Init();
        // Load our fonts, with a huge size
        auto font = TTF_OpenFont( FONT_PATH, 16 );
        if (font == nullptr) {
            //throw std::runtime_error("Can't open fond");
        }

        text_surface = TTF_RenderText_Blended( font, "Score: ", textColor );

        TTF_CloseFont(font);
        TTF_Quit();
    }

    start_game::~start_game() {
        SDL_FreeSurface(text_surface);
    }

    void start_game::render() {
        // (*scene_)->draw_texture(text_surface->pixels, text_surface->w, text_surface->h);
        //render_surface(text_surface);
    }
}