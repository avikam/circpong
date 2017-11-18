#include <windows.h>
#include "src/game.h"

//int main() {
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    pong::game g;

    g.play();
    return 0;
}