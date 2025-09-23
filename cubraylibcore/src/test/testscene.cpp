#include "testscene.h"
#include "../core/util/globals.h"
#include <memory>

TestScene::TestScene() {
    bgColor = RAYWHITE;
}

void TestScene::create() {
    Scene::create();

    float centerX = (float)Globals::WINDOW_WIDTH / 2 - 130;
    float centerY = (float)Globals::WINDOW_HEIGHT / 2;

    funnytext = add(std::make_unique<FunnyText>("kubach raylib", centerX, centerY, 40, DARKGREEN));
    funnytext->speed = 60.0f;
    funnytext->amplitude = 80.0f;

    auto window = std::make_unique<TestWindow>();
    window->onClose = [this]() {
        //
        };
    testWindow = add(std::move(window));

    auto window2 = std::make_unique<TestWindowTwo>();
    window2->onClose = [this]() {
        //
        };
    lameWindow = add(std::move(window2));
}

void TestScene::update(float deltaTime) {
    Scene::update(deltaTime);
}