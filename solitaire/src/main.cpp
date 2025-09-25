#include "core/game.h"
#include "core/util/globals.h"
#include "solitaire/menuscene.h"

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

int main() {
    Game gameInstance(Globals::INIT_WINDOW_WIDTH, Globals::INIT_WINDOW_HEIGHT, Globals::INIT_WINDOW_TITLE);
    Globals::game = &gameInstance;
    Globals::game->switchScene<MenuScene>();
    Globals::game->run();

    return 0;
}