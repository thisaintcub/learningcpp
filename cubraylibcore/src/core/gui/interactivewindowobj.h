#pragma once
#include "windowobj.h"
#include <raylib.h>
#include <string>
#include <functional>

class InteractiveWindowobj : public Windowobj {
public:
    InteractiveWindowobj(float x, float y, float width, float height, const std::string& title);
    virtual ~InteractiveWindowobj() = default;

    void update(float deltaTime) override;
    void draw() override;
    void setPosition(float x, float y) override;

    bool draggable = true;
    bool resizable = false;
    std::function<void(Vector2)> onMove = nullptr;

private:
    bool isDragging = false;
    bool isResizing = false;
    Vector2 dragOffset = { 0, 0 };

    static constexpr float TITLE_BAR_HEIGHT = 24.0f;
    static constexpr float BUTTON_SIZE = 16.0f;
    static constexpr float RESIZE_HANDLE_SIZE = 12.0f;

    void handleDragging();
    void handleResizing();
    bool isMouseInTitleBar() const;
    bool isMouseInResizeHandle() const;
};