#include "objectman.h"

void Objectman::remove(Object* obj) {
    if (updating)
        objectsToRemove.push_back(obj);
    else {
        objects.erase(
            std::remove_if(objects.begin(), objects.end(),
                [obj](const std::unique_ptr<Object>& ptr) {
                    return ptr.get() == obj;
                }),
            objects.end()
        );
    }
}

void Objectman::clear() {
    if (updating) {
        for (auto& obj : objects)
            objectsToRemove.push_back(obj.get());
    }
    else
        objects.clear();
}

void Objectman::updateAll(float deltaTime) {
    updating = true;

    for (auto& obj : objects) {
        if (obj && obj->active)
            obj->update(deltaTime);
    }

    updating = false;
    processAddRemove();
}

void Objectman::renderAll() {
    for (auto& obj : objects) {
        if (obj && obj->visible)
            obj->render();
    }
}

void Objectman::sortByDepth() {
    std::sort(objects.begin(), objects.end(),
        [](const std::unique_ptr<Object>& a, const std::unique_ptr<Object>& b) {
            return a->depth < b->depth;
        });
}

void Objectman::processAddRemove() {
    for (auto& obj : objectsToAdd)
        objects.push_back(std::move(obj));

    objectsToAdd.clear();

    for (Object* objToRemove : objectsToRemove) {
        objects.erase(
            std::remove_if(objects.begin(), objects.end(),
                [objToRemove](const std::unique_ptr<Object>& ptr) {
                    return ptr.get() == objToRemove;
                }),
            objects.end()
        );
    }
    objectsToRemove.clear();

    if (!objectsToAdd.empty())
        sortByDepth();
}