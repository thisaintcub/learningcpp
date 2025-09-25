#include "menuscene.h"
#include "gamescene.h"
#include "../core/util/globals.h"

MenuScene::MenuScene() {
    bgColor = RAYWHITE;
}

void MenuScene::create() {
    Scene::create();
}

void MenuScene::update(float deltaTime) {
    Scene::update(deltaTime);

    if (IsKeyPressed(KEY_ENTER))
        Globals::game->switchScene<GameScene>();
}