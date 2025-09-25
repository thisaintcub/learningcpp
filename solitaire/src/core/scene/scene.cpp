#include "scene.h"
#include "subscene.h"

void SubsceneDeleter::operator()(Subscene* ptr) const {
    delete ptr;
}

Scene::Scene() = default;

Scene::~Scene() {
    destroy();
}

void Scene::update(float deltaTime) {
    objectMan.updateAll(deltaTime);
}

void Scene::draw() {
    if (persistentDraw || currentSubScene == nullptr)
        ClearBackground(bgColor);

    objectMan.drawAll();

    if (currentSubScene != nullptr)
        currentSubScene->draw();
}

void Scene::openSubScene(SubscenePtr subscene) {
    subSceneResetRequested = true;
    pendingSubScene = std::move(subscene);
}

void Scene::closeSubScene() {
    subSceneResetRequested = true;
}

void Scene::resetSubScene() {
    if (currentSubScene != nullptr) {
        if (currentSubScene->closeCallback)
            currentSubScene->closeCallback();

        if (destroySubScenes)
            currentSubScene->destroy();

        currentSubScene.reset();
    }

    currentSubScene = std::move(pendingSubScene);
    pendingSubScene.reset();

    if (currentSubScene != nullptr) {
        currentSubScene->parentScene = this;

        if (!currentSubScene->isCreated) {
            currentSubScene->isCreated = true;
            currentSubScene->create();
        }

        if (currentSubScene->openCallback)
            currentSubScene->openCallback();
    }
}

void Scene::tryUpdate(float deltaTime) {
    if (persistentUpdate || currentSubScene == nullptr)
        update(deltaTime);

    if (subSceneResetRequested) {
        subSceneResetRequested = false;
        resetSubScene();
    }

    if (currentSubScene != nullptr)
        currentSubScene->tryUpdate(deltaTime);
}