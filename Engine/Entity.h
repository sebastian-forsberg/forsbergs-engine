#pragma once

// Entity.h /////////////////////////
// F-25 ENGINE / Base Game Object   |_________________________________________.
//   You do not inherit from entity, but you extend it through different      |
// components, which you create by deriving from Component. The AddComponent  |
// function is an example of a so-called "factory" function, which creates    |
// objects which are then managed by the object and finally dealloced         |
// automatically with the deconstructor.                                      |
///////////////////////////////////////// (c)opyright sebastian jensen / 2025 /

#include <utility> // std::forward

#include "Common.h"
#include "Collections/LinkedList.h"

#include "Component.h"

class Entity
{
    LinkedList<Component *> components;

public:
    bool active;
    Vector2 position;

    // Showing of some true C++ insanity here.
    // This allows us to act as a polymorphic proxy
    // for the constructor of any class derived from
    // Component. The pros are that we make the allocation
    // and we free, so it is completely symmetrical,
    // but the downside is that it takes longer to compile,
    // is hard to debug and also pretty hard to read and
    // understand.
    template <typename T, typename... Args>
    T *AddComponent(Args &&...args)
    {
        T *component = new T(std::forward<Args>(args)...);
        component->owner = this;
        components.InsertLast(component);
        return component;
    }

    template <typename T>
    T *GetComponent()
    {
        for (int i = 0; i < components.Count(); i++)
        {
            Result<Component *> c = components.GetDataAt(i);
            if (c.valid)
            {
                // Note: Dynamic cast is really slow!
                T *casted = dynamic_cast<T *>(c.data);
                if (casted)
                {
                    return casted;
                }
            }
        }
        return nullptr;
    }

    void OnUpdate(float deltaTime)
    {
        for (int i = 0; i < components.Count(); i++)
        {
            Result<Component *> c = components.GetDataAt(i);
            if (c.valid)
            {
                c.data->OnUpdate(deltaTime);
            }
        }
    }

    ~Entity()
    {
        for (int i = 0; i < components.Count(); i++)
        {
            Result<Component *> c = components.GetDataAt(i);
            if (c.valid)
            {
                if (c.data)
                {
                    delete c.data;
                }
            }
        }
    }
};