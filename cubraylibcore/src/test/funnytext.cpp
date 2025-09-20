#include "funnytext.h"
#include <cmath>

FunnyText::FunnyText(const std::string& text, float x, float y, int fontSize, Color color)
    : text(text), fontSize(fontSize), color(color) {
    position.x = x;
    position.y = y;
    baseY = y;
}

void FunnyText::update(float deltaTime) {
    time += deltaTime;

    position.y = baseY + sin(time * speed / 50.0f) * amplitude;
}

void FunnyText::render() {
    DrawText(text.c_str(), (int)position.x, (int)position.y, fontSize, color);
}