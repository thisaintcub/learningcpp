#pragma once
#include "../core/gui/interactivewindowobj.h"

class TestWindowTwo : public InteractiveWindowobj {
public:
    TestWindowTwo();

protected:
    void drawContent() override;

private:
    bool buttonClicked = false;
};