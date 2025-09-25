#include "screen.h"
#include "util/globals.h"
#include <algorithm>
#include <iostream>

Screen::Screen() : initialized(false), scale(1.0f), offsetX(0), offsetY(0) {
}

Screen::~Screen() {
    if (initialized)
        UnloadRenderTexture(renderTexture);
}

void Screen::init(int baseWidth, int baseHeight) {
    this->baseWidth = baseWidth;
    this->baseHeight = baseHeight;

    renderTexture = LoadRenderTexture(baseWidth, baseHeight);
    SetTextureFilter(renderTexture.texture, TEXTURE_FILTER_POINT);

    calculateScale(Globals::WINDOW_WIDTH, Globals::WINDOW_HEIGHT);

    initialized = true;

    std::cout << "Info: Screen initialized: " << baseWidth << "x" << baseHeight << std::endl;
}

void Screen::beginRender() {
    if (!initialized) return;

    BeginTextureMode(renderTexture);
    ClearBackground(BLACK);
}

void Screen::endRender() {
    if (!initialized) return;

    EndTextureMode();

    ClearBackground(BLACK);

    Rectangle source = {
        0.0f,
        0.0f,
        (float)renderTexture.texture.width,
        -(float)renderTexture.texture.height
    };

    Rectangle dest = {
        (float)offsetX,
        (float)offsetY,
        (float)scaledWidth,
        (float)scaledHeight
    };

    DrawTexturePro(renderTexture.texture, source, dest, { 0, 0 }, 0.0f, WHITE);

    if (offsetX > 0) {
        DrawRectangle(0, 0, offsetX, Globals::WINDOW_HEIGHT, BLACK);
        DrawRectangle(offsetX + scaledWidth, 0, offsetX, Globals::WINDOW_HEIGHT, BLACK);
    }
    if (offsetY > 0) {
        DrawRectangle(0, 0, Globals::WINDOW_WIDTH, offsetY, BLACK);
        DrawRectangle(0, offsetY + scaledHeight, Globals::WINDOW_WIDTH, offsetY, BLACK);
    }
}

void Screen::onResize(int windowWidth, int windowHeight) {
    calculateScale(windowWidth, windowHeight);
}

void Screen::calculateScale(int windowWidth, int windowHeight) {
    float scaleX = (float)windowWidth / baseWidth;
    float scaleY = (float)windowHeight / baseHeight;

    scale = std::min(scaleX, scaleY);

    scaledWidth = (int)(baseWidth * scale);
    scaledHeight = (int)(baseHeight * scale);

    offsetX = (windowWidth - scaledWidth) / 2;
    offsetY = (windowHeight - scaledHeight) / 2;

    std::cout << "Info: Scale calculated: " << scale << " (" << scaledWidth << "x" << scaledHeight << ")" << std::endl;
    std::cout << "Info: Offset: " << offsetX << ", " << offsetY << std::endl;
}