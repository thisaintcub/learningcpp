#include "windowobj.h"
#include <raygui.h>
#include <algorithm>

Windowobj::Windowobj(float x, float y, float width, float height, const std::string& title)
    : bounds{ x, y, width, height }, title(title) {
    depth = 100;
}

void Windowobj::update(float deltaTime) {
    if (!open || !active) return;
}

void Windowobj::draw() {
    if (!open || !visible) return;

    GuiPanel(bounds, nullptr);

    Rectangle titleBar = { bounds.x, bounds.y, bounds.width, TITLE_BAR_HEIGHT };
    GuiPanel(titleBar, title.c_str());

    if (closeable) {
        Rectangle closeBtn = {
            bounds.x + bounds.width - BUTTON_SIZE - 4,
            bounds.y + 4,
            BUTTON_SIZE,
            BUTTON_SIZE
        };

        if (GuiButton(closeBtn, "x")) {
            if (onClose)
                onClose();

            close();
        }
    }

    if (minimizable) {
        Rectangle minBtn = {
            bounds.x + bounds.width - (closeable ? BUTTON_SIZE * 2 + 8 : BUTTON_SIZE + 4),
            bounds.y + 4,
            BUTTON_SIZE,
            BUTTON_SIZE
        };

        if (GuiButton(minBtn, "-")) {
            if (onMinimize)
                onMinimize();
        }
    }

    drawContent();
}

void Windowobj::setPosition(float x, float y) {
    bounds.x = x;
    bounds.y = y;
}

void Windowobj::setSize(float width, float height) {
    bounds.width = std::max(width, minSize.x);
    bounds.height = std::max(height, minSize.y);

    if (maxSize.x > 0) bounds.width = std::min(bounds.width, maxSize.x);
    if (maxSize.y > 0) bounds.height = std::min(bounds.height, maxSize.y);

    if (onResize) onResize({ bounds.width, bounds.height });
}

void Windowobj::setTitle(const std::string& newTitle) {
    title = newTitle;
}

Rectangle Windowobj::getContentArea() const {
    return {
        bounds.x + 1,
        bounds.y + TITLE_BAR_HEIGHT + 1,
        bounds.width - 2,
        bounds.height - TITLE_BAR_HEIGHT - 2
    };
}