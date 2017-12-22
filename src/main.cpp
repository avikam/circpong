#include <string>
#include "src/external/inih-master/INIReader.h"
#include "src/config.h"
#include "src/game.h"

namespace pong {
    static config init_config(int argc, const char* const argv[]){
        config conf {};
        if (argc > 1) {
            std::string arg1 { argv[1] };

            INIReader reader(arg1);

            if (reader.ParseError() < 0) {
                std::cout << "Can't load "<< arg1 << "\n";
            }

            conf.max_score = static_cast<int>(reader.GetInteger("config", "max_score", constants::max_score));
        }
        // conf.max_seconds_idle = 2;

        return conf;
    };
}

int main(int argc, const char* const argv[]) {
    auto conf = pong::init_config(argc, argv);

    pong::game g { conf };
    g.play();
    return 0;
}
