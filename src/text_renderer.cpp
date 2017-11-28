//
// Created by Avikam Agur on 20/11/2017.
//

#include "src/start_game.h"

#define FONT_PATH "resources/fonts/NES-Chimera/NES-Chimera.ttf"

namespace pong {
    static void render_surface(SDL_Surface* surface) {


    }

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

        score_1 = TTF_RenderText_Blended( font, "Score: 1", textColor );
        score_2 = TTF_RenderText_Blended( font, "Score: 3", textColor );

        TTF_CloseFont(font);
        TTF_Quit();
    }

    start_game::~start_game() {
        SDL_FreeSurface(score_1);
        SDL_FreeSurface(score_2);
    }

    void start_game::render() {
        (*scene_)->draw_texture(score_1->pixels, score_1->w, score_1->h, 0);
        (*scene_)->draw_texture(score_2->pixels, score_2->w, score_2->h, 1);
    }
}
