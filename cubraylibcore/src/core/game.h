#pragma once
#include "scene/sceneman.h"
#include <raylib.h>
#include <string>

class Game {
public:
    Game(int width, int height, const std::string& title);
    ~Game();

    void run();

    template<typename T, typename... Args>
    void switchScene(Args&&... args) {
        sceneman.switchScene<T>(std::forward<Args>(args)...);
    }

    bool shouldClose() const;

private:
    void update(float deltaTime);
    void draw();
    void handleResize();
    void handleFocusChange();

    Sceneman& sceneman;

    bool initialized;
    bool lastFocusState;
};