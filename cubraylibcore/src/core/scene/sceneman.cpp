#include "sceneman.h"

Sceneman& Sceneman::getInstance() {
    static Sceneman instance;
    return instance;
}

void Sceneman::switchScene(std::unique_ptr<Scene> scene) {
    pendingScene = std::move(scene);
    sceneChangeRequested = true;
}

void Sceneman::pushScene(std::unique_ptr<Scene> scene) {
    sceneStack.push(std::move(scene));

    if (sceneStack.size() == 1) {
        auto& currentScene = sceneStack.top();
        if (!currentScene->isCreated) {
            currentScene->isCreated = true;
            currentScene->create();
        }
    }
}

void Sceneman::popScene() {
    if (!sceneStack.empty()) {
        auto& currentScene = sceneStack.top();
        currentScene->destroy();
        sceneStack.pop();
    }
}

void Sceneman::update(float deltaTime) {
    if (sceneChangeRequested && pendingScene != nullptr) {
        while (!sceneStack.empty())
            popScene();

        pushScene(std::move(pendingScene));
        pendingScene.reset();
        sceneChangeRequested = false;
    }

    if (hasActiveScene()) {
        auto& currentScene = sceneStack.top();
        if (!currentScene->isCreated) {
            currentScene->isCreated = true;
            currentScene->create();
        }

        currentScene->tryUpdate(deltaTime);
    }
}

void Sceneman::draw() {
    if (hasActiveScene()) {
        auto& currentScene = sceneStack.top();
        currentScene->draw();
    }
}

void Sceneman::onFocusLost() {
    if (hasActiveScene())
        getCurrentScene()->onFocusLost();
}

void Sceneman::onFocus() {
    if (hasActiveScene())
        getCurrentScene()->onFocus();
}

void Sceneman::onResize(int width, int height) {
    if (hasActiveScene())
        getCurrentScene()->onResize(width, height);
}

Scene* Sceneman::getCurrentScene() const {
    return hasActiveScene() ? sceneStack.top().get() : nullptr;
}

bool Sceneman::hasActiveScene() const {
    return !sceneStack.empty();
}