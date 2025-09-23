#pragma once
#include "../core/gui/interactivewindowobj.h"

class TestWindow : public InteractiveWindowobj {
public:
    TestWindow();

protected:
    void drawContent() override;

private:
    bool buttonClicked = false;
};