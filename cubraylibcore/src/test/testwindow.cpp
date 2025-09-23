#include "testwindow.h"
#include <raygui.h>

TestWindow::TestWindow() : InteractiveWindowobj(50, 50, 300, 200, "???? SHTOOOOOOOOOO") {
    draggable = true;
    resizable = false;
    closeable = false;
    minimizable = false;
}

void TestWindow::drawContent() {
    Rectangle contentArea = getContentArea();

    GuiLabel(Rectangle{ contentArea.x + 10, contentArea.y + 5, 200, 20 }, "Z");

    if (GuiButton(Rectangle{ contentArea.x + 10, contentArea.y + 50, 100, 30 }, "knopk"))
        buttonClicked = !buttonClicked;

    if (buttonClicked)
        GuiLabel(Rectangle{ contentArea.x + 10, contentArea.y + 80, 200, 20 }, "sprytannoe kokashk...");

    static float sliderValue = 50.0f;
    GuiSlider(Rectangle{ contentArea.x + 30, contentArea.y + 110, 150, 20 }, "Min", "Max", &sliderValue, 0.0f, 100.0f);
}