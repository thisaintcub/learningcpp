#include "subscene.h"

Subscene::Subscene(Color backgroundColor) : Scene(), backgroundColor(backgroundColor) {
    persistentUpdate = false;
    persistentDraw = false;
}

void Subscene::draw() {
    if (backgroundColor.a > 0)
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), backgroundColor);

    if (currentSubScene != nullptr)
        currentSubScene->draw();
}

void Subscene::close() {
    if (parentScene != nullptr && parentScene->currentSubScene.get() == this)
        parentScene->closeSubScene();
}