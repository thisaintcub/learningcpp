#pragma once
#include <raylib.h>

class Screen {
public:
    Screen();
    ~Screen();

    void init(int baseWidth = 1280, int baseHeight = 720);

    void beginRender();

    void endRender();

    void onResize(int windowWidth, int windowHeight);

    float getScale() const { return scale; }

    int getBaseWidth() const { return baseWidth; }
    int getBaseHeight() const { return baseHeight; }

    int getScaledWidth() const { return scaledWidth; }
    int getScaledHeight() const { return scaledHeight; }

    int getOffsetX() const { return offsetX; }
    int getOffsetY() const { return offsetY; }

private:
    void calculateScale(int windowWidth, int windowHeight);

    RenderTexture2D renderTexture;

    int baseWidth, baseHeight;
    int scaledWidth, scaledHeight;
    int offsetX, offsetY;
    float scale;

    bool initialized;
};