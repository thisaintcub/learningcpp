#pragma once

#include "object.h"
#include <vector>
#include <memory>
#include <algorithm>

class Objectman {
private:
    std::vector<std::unique_ptr<Object>> objects;
    std::vector<std::unique_ptr<Object>> objectsToAdd;
    std::vector<Object*> objectsToRemove;
    bool updating = false;

    void processAddRemove();

public:
    Objectman() = default;
    ~Objectman() = default;

    template<typename T>
    T* add(std::unique_ptr<T> object) {
        static_assert(std::is_base_of<Object, T>::value);
        T* ptr = object.get();

        if (updating)
            objectsToAdd.push_back(std::move(object));
        else {
            objects.push_back(std::move(object));
            sortByDepth();
        }

        return ptr;
    }

    void remove(Object* obj);

    void clear();

    void updateAll(float deltaTime);

    void renderAll();

    void sortByDepth();

    size_t getObjectCount() const { return objects.size(); }

    template<typename T>
    T* findObject() {
        for (auto& obj : objects) {
            T* casted = dynamic_cast<T*>(obj.get());
            if (casted) return casted;
        }
        return nullptr;
    }

    template<typename T>
    std::vector<T*> findObjects() {
        std::vector<T*> result;
        for (auto& obj : objects) {
            T* casted = dynamic_cast<T*>(obj.get());
            if (casted) result.push_back(casted);
        }
        return result;
    }
};
