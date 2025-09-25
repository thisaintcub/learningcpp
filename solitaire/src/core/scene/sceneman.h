#pragma once
#include "scene.h"
#include <memory>
#include <stack>

class Sceneman {
public:
    static Sceneman& getInstance();

    template<typename T, typename... Args>
    void switchScene(Args&&... args);

    void switchScene(std::unique_ptr<Scene> scene);
    void pushScene(std::unique_ptr<Scene> scene);
    void popScene();

    void update(float deltaTime);
    void draw();

    void onFocusLost();
    void onFocus();
    void onResize(int width, int height);

    Scene* getCurrentScene() const;
    bool hasActiveScene() const;

private:
    Sceneman() = default;
    ~Sceneman() = default;
    Sceneman(const Sceneman&) = delete;
    Sceneman& operator=(const Sceneman&) = delete;

    std::stack<std::unique_ptr<Scene>> sceneStack;
    std::unique_ptr<Scene> pendingScene = nullptr;
    bool sceneChangeRequested = false;
};

template<typename T, typename... Args>
void Sceneman::switchScene(Args&&... args) {
    static_assert(std::is_base_of_v<Scene, T>, "T must be scene");
    auto scene = std::make_unique<T>(std::forward<Args>(args)...);
    switchScene(std::move(scene));
}