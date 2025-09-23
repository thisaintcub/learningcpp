#pragma once
#include "../core/scene/scene.h"
#include "funnytext.h"
#include "testwindow.h"
#include "testwindowtwo.h"

class TestScene : public Scene {
public:
    TestScene();

    void create() override;
    void update(float deltaTime) override;

private:
    FunnyText* funnytext;
    TestWindow* testWindow;
    TestWindowTwo* lameWindow;
};