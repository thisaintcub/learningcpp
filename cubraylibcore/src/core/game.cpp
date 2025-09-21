#include "game.h"
#include "util/globals.h"

Game::Game(int width, int height, const std::string& title) : sceneman(Sceneman::getInstance()), initialized(false) {
    InitWindow(width, height, title.c_str());
    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN);
    SetTargetFPS(60);
    InitAudioDevice();

    Globals::WINDOW_WIDTH = width;
    Globals::WINDOW_HEIGHT = height;

    initialized = true;
}

Game::~Game() {
    if (initialized) {
        CloseAudioDevice();
        CloseWindow();
    }
}

void Game::run() {
    while (!shouldClose()) {
        handleResize();
        handleFocusChange();

        float deltaTime = GetFrameTime();
        if (IsWindowFocused())
            update(deltaTime);

        BeginDrawing();
        draw();
        EndDrawing();
    }
}

bool Game::shouldClose() const {
    return WindowShouldClose();
}

void Game::update(float deltaTime) {
    sceneman.update(deltaTime);
}

void Game::draw() {
    sceneman.draw();
}

void Game::handleResize() {
    if (IsWindowResized()) {
        Globals::WINDOW_WIDTH = GetScreenWidth();
        Globals::WINDOW_HEIGHT = GetScreenHeight();
        sceneman.onResize(Globals::WINDOW_WIDTH, Globals::WINDOW_HEIGHT);
    }
}

void Game::handleFocusChange() {
    bool currentFocusState = IsWindowFocused();

    if (currentFocusState != lastFocusState) {
        if (currentFocusState)
            sceneman.onFocus();
        else
            sceneman.onFocusLost();

        lastFocusState = currentFocusState;
    }
}