#pragma once

#include "../game.h"
#include <string>

namespace Globals {
    inline constexpr int INIT_WINDOW_WIDTH = 1280;
    inline constexpr int INIT_WINDOW_HEIGHT = 720;
    inline const std::string INIT_WINDOW_TITLE = "cubcubcub";

    // make it global so it works everywhere
    static Game* game = nullptr;

    static int WINDOW_WIDTH = INIT_WINDOW_WIDTH;
    static int WINDOW_HEIGHT = INIT_WINDOW_HEIGHT;
}