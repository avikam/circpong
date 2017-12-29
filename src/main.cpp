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
            conf.max_seconds_idle_instruction = static_cast<int>(reader.GetInteger("config", "instruction_idle", constants::max_seconds_idle_instruction));
            conf.max_seconds_idle = static_cast<int>(reader.GetInteger("config", "idle", constants::max_seconds_idle));
            conf.ball_size = static_cast<float>(reader.GetReal("config", "ball_size", constants::ball_size));
            conf.radius = static_cast<float>(reader.GetReal("config", "radius", constants::radius));
            conf.initial_velocity = static_cast<float>(reader.GetReal("config", "initial_velocity", constants::initial_velocity));
            conf.window_size = static_cast<int>(reader.GetInteger("config", "window_size", 0));
            conf.window_pos_x = static_cast<int>(reader.GetInteger("config", "window_pos_x", -1));
            conf.window_pos_y = static_cast<int>(reader.GetInteger("config", "window_pos_y", -1));
        }

        return conf;
    };
}

#ifdef _WIN32
#include "windows.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    LPWSTR * szArgList;
    int argc;
    int i;
    auto ** argv = new char*[argc];

    szArgList = CommandLineToArgvW(GetCommandLineW(), &argc);
    if( NULL == szArgList )
    {
        wprintf(L"CommandLineToArgvW failed\n");
        return 0;
    }
    else {
        for(i = 0; i<argc; i++){
            auto len = wcslen(szArgList[i]);
            argv[i] = new char[len+1];
            wcstombs (argv[i], szArgList[i]  ,len+1);
            std::cout << i << ": " << argv[i] << "\n";
        }
    }

#else
    int main(int argc, const char* const argv[]) {
#endif
    auto conf = pong::init_config(argc, argv);

    pong::game g { conf };
    g.play();
    return 0;
}