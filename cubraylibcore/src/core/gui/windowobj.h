#pragma once
#include "../object/object.h"
#include <raylib.h>
#include <string>
#include <functional>

class Windowobj : public Object {
public:
    Windowobj(float x, float y, float width, float height, const std::string& title);
    virtual ~Windowobj() = default;

    void update(float deltaTime) override;
    void draw() override;

    virtual void setPosition(float x, float y);
    void setSize(float width, float height);
    void setTitle(const std::string& title);

    Vector2 getPosition() const { return { bounds.x, bounds.y }; }
    Vector2 getSize() const { return { bounds.width, bounds.height }; }
    Rectangle getBounds() const { return bounds; }
    bool isOpen() const { return open; }

    void close() { open = false; }
    void show() { open = true; }

    bool closeable = true;
    bool minimizable = false;

    std::function<void()> onClose = nullptr;
    std::function<void()> onMinimize = nullptr;
    std::function<void(Vector2)> onResize = nullptr;

protected:
    virtual void drawContent() {}

    Rectangle getContentArea() const;

    Rectangle bounds;
    std::string title;
    bool open = true;
    Vector2 minSize = { 200, 100 };
    Vector2 maxSize = { 800, 600 };

    static constexpr float TITLE_BAR_HEIGHT = 24.0f;
    static constexpr float RESIZE_HANDLE_SIZE = 12.0f;
    static constexpr float BUTTON_SIZE = 16.0f;
};