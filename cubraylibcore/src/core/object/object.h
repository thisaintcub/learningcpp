#pragma once

class Object {
public:
    Object() = default;
    virtual ~Object() = default;

    virtual void update(float deltaTime) {}
    virtual void render() {}

    bool active = true;
    bool visible = true;
    int depth = 0;
};