#include "testwindowtwo.h"
#include <raygui.h>

TestWindowTwo::TestWindowTwo() : InteractiveWindowobj(100, 100, 300, 200, "resizable") {
    draggable = true;
    resizable = true;
    closeable = true;
    minimizable = true;
}

void TestWindowTwo::drawContent() {
    Rectangle contentArea = getContentArea();

    GuiLabel(Rectangle{ contentArea.x + 10, contentArea.y + 5, 200, 20 },
        "wow so cool");
}