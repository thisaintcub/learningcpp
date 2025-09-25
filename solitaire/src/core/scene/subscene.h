#pragma once
#include "scene.h"

class Subscene : public Scene {
public:
    explicit Subscene(Color backgroundColor = { 0, 0, 0, 128 });
    virtual ~Subscene() = default;

    std::function<void()> openCallback = nullptr;
    std::function<void()> closeCallback = nullptr;

    void draw() override;
    void close();

private:
    Scene* parentScene = nullptr;
    Color backgroundColor;

    friend class Scene;
};