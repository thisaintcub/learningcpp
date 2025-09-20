#pragma once
#include "../core/object/object.h"
#include "raylib.h"
#include <string>

class FunnyText : public Object {
public:
    FunnyText(const std::string& text, float x, float y, int fontSize = 20, Color color = WHITE);

    void update(float deltaTime) override;
    void render() override;

    Vector2 position;
    std::string text;
    int fontSize;
    Color color;

    float speed = 50.0f;
    float amplitude = 100.0f;
    float time = 0.0f;
    float baseY;
};