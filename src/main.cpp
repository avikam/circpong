#include "src/config.h"
#include "src/game.h"

namespace pong {
    static config init_config(){
        config conf {};
        // conf.max_seconds_idle = 2;
        conf.max_score = 2;

        return conf;
    };
}

int main() {
    auto conf = pong::init_config();

    pong::game g { conf };
    g.play();
    return 0;
}