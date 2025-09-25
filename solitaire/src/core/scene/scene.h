#pragma once
#include "raylib.h"
#include "../object/objectman.h"
#include <functional>
#include <memory>

class Subscene;

struct SubsceneDeleter {
    void operator()(Subscene* ptr) const;
};

using SubscenePtr = std::unique_ptr<Subscene, SubsceneDeleter>;

class Scene {
public:
    Scene();
    virtual ~Scene();

    virtual void create() {}
    virtual void update(float deltaTime);
    virtual void draw();
    virtual void destroy() {}

    virtual void onFocusLost() {}
    virtual void onFocus() {}
    virtual void onResize(int width, int height) {}

    void openSubScene(SubscenePtr subscene);
    void closeSubScene();

    template<typename T>
    T* add(std::unique_ptr<T> object) {
        return objectMan.add(std::move(object));
    }

    void remove(Object* object) {
        objectMan.remove(object);
    }

    void clear() {
        objectMan.clear();
    }

    template<typename T>
    T* findObject() {
        return objectMan.findObject<T>();
    }

    template<typename T>
    std::vector<T*> findObjects() {
        return objectMan.findObjects<T>();
    }

    bool persistentUpdate = false;
    bool persistentDraw = true;
    bool destroySubScenes = true;
    Color bgColor = BLACK;

private:
    void resetSubScene();
    void tryUpdate(float deltaTime);

    Objectman objectMan;
    SubscenePtr currentSubScene = nullptr;
    SubscenePtr pendingSubScene = nullptr;
    bool subSceneResetRequested = false;
    bool isCreated = false;

    friend class Sceneman;
    friend class Subscene;
};