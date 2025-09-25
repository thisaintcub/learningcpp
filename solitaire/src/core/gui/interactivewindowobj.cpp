#include "interactivewindowobj.h"
#include <raygui.h>
#include <algorithm>

InteractiveWindowobj::InteractiveWindowobj(float x, float y, float width, float height, const std::string& title)
    : Windowobj(x, y, width, height, title) {
}

void InteractiveWindowobj::update(float deltaTime) {
    Windowobj::update(deltaTime);

    if (open && active) {
        handleDragging();
        if (resizable)
            handleResizing();
    }
}

void InteractiveWindowobj::draw() {
    if (!open || !visible) return;

    Windowobj::draw();

    if (resizable) {
        Rectangle resizeHandle = {
            bounds.x + bounds.width - RESIZE_HANDLE_SIZE,
            bounds.y + bounds.height - RESIZE_HANDLE_SIZE,
            RESIZE_HANDLE_SIZE,
            RESIZE_HANDLE_SIZE
        };
        GuiPanel(resizeHandle, nullptr);
    }
}

void InteractiveWindowobj::setPosition(float x, float y) {
    Windowobj::setPosition(x, y);

    if (onMove)
        onMove({ x, y });
}

void InteractiveWindowobj::handleDragging() {
    if (!draggable) return;

    Vector2 mousePos = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isMouseInTitleBar()) {
        isDragging = true;
        Vector2 position = getPosition();
        dragOffset = {
            mousePos.x - position.x,
            mousePos.y - position.y
        };
    }

    if (isDragging) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            setPosition(mousePos.x - dragOffset.x, mousePos.y - dragOffset.y);
        else
            isDragging = false;
    }
}

void InteractiveWindowobj::handleResizing() {
    Vector2 mousePos = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isMouseInResizeHandle())
        isResizing = true;

    if (isResizing) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            float newWidth = mousePos.x - bounds.x;
            float newHeight = mousePos.y - bounds.y;
            setSize(newWidth, newHeight);
        }
        else
            isResizing = false;
    }
}

bool InteractiveWindowobj::isMouseInTitleBar() const {
    Vector2 mousePos = GetMousePosition();
    Rectangle bounds = getBounds();
    Rectangle titleBar = { bounds.x, bounds.y, bounds.width, TITLE_BAR_HEIGHT };

    float buttonAreaWidth = 0;
    if (closeable) buttonAreaWidth += BUTTON_SIZE + 4;
    if (minimizable) buttonAreaWidth += BUTTON_SIZE + 4;

    Rectangle draggableArea = {
        titleBar.x,
        titleBar.y,
        titleBar.width - buttonAreaWidth,
        titleBar.height
    };

    return CheckCollisionPointRec(mousePos, draggableArea);
}

bool InteractiveWindowobj::isMouseInResizeHandle() const {
    Vector2 mousePos = GetMousePosition();
    Rectangle resizeHandle = {
        bounds.x + bounds.width - RESIZE_HANDLE_SIZE,
        bounds.y + bounds.height - RESIZE_HANDLE_SIZE,
        RESIZE_HANDLE_SIZE,
        RESIZE_HANDLE_SIZE
    };
    return CheckCollisionPointRec(mousePos, resizeHandle);
}