#include "game.h"
#include "util/globals.h"
#include <iostream>

Game::Game(int width, int height, const std::string& title) : sceneman(Sceneman::getInstance()),
initialized(false), wasResizing(false), windowedWidth(width), windowedHeight(height),
windowedPosX(100), windowedPosY(100) {
    InitWindow(width, height, title.c_str());
    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN);
    SetTargetFPS(60);
    InitAudioDevice();

    Globals::WINDOW_WIDTH = width;
    Globals::WINDOW_HEIGHT = height;

    screen.init(1280, 720);

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
        handleFullscreenInput();

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
    screen.beginRender();

    sceneman.draw();

    screen.endRender();
}

void Game::handleResize() {
    bool currentlyResizing = IsWindowResized();

    if (currentlyResizing) {
        TraceLog(LOG_INFO, "resized window");
        Globals::WINDOW_WIDTH = GetScreenWidth();
        Globals::WINDOW_HEIGHT = GetScreenHeight();
        std::cout << "INFO: width " << Globals::WINDOW_WIDTH << std::endl;
        std::cout << "INFO: height " << Globals::WINDOW_HEIGHT << std::endl;

        screen.onResize(Globals::WINDOW_WIDTH, Globals::WINDOW_HEIGHT);

        sceneman.onResize(Globals::WINDOW_WIDTH, Globals::WINDOW_HEIGHT);
        wasResizing = true;
    }
    else if (wasResizing)
        wasResizing = false;
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

void Game::handleFullscreenInput() {
    if (IsKeyPressed(KEY_F11)) {
        if (IsWindowFullscreen()) {
            ToggleFullscreen();
            std::cout << "INFO: Switched to windowed mode" << std::endl;
        }
        else {
            if (!IsWindowMaximized()) {
                windowedWidth = GetScreenWidth();
                windowedHeight = GetScreenHeight();
                windowedPosX = GetWindowPosition().x;
                windowedPosY = GetWindowPosition().y;
            }

            ToggleFullscreen();
            std::cout << "INFO: Switched to fullscreen exclusive" << std::endl;
        }

        Globals::WINDOW_WIDTH = GetScreenWidth();
        Globals::WINDOW_HEIGHT = GetScreenHeight();
        screen.onResize(Globals::WINDOW_WIDTH, Globals::WINDOW_HEIGHT);
    }

    if (IsKeyPressed(KEY_F12)) {
        if (IsWindowMaximized() && !IsWindowFullscreen()) {
            RestoreWindow();
            SetWindowSize(windowedWidth, windowedHeight);
            SetWindowPosition(windowedPosX, windowedPosY);
            std::cout << "INFO: Switched to windowed mode" << std::endl;
        }
        else {
            if (!IsWindowFullscreen() && !IsWindowMaximized()) {
                windowedWidth = GetScreenWidth();
                windowedHeight = GetScreenHeight();
                windowedPosX = GetWindowPosition().x;
                windowedPosY = GetWindowPosition().y;
            }

            if (IsWindowFullscreen())
                ToggleFullscreen();

            MaximizeWindow();
            std::cout << "INFO: Switched to fullscreen windowed" << std::endl;
        }

        Globals::WINDOW_WIDTH = GetScreenWidth();
        Globals::WINDOW_HEIGHT = GetScreenHeight();
        screen.onResize(Globals::WINDOW_WIDTH, Globals::WINDOW_HEIGHT);
    }
}