#pragma once

// Component.h /////////////////////////
// F-25 ENGINE / Base Component Class  |______________________________________.
//   Deriving from this class and composing several of these together is how  |
// you compose Entities that have different behaviours.                       |
///////////////////////////////////////// (c)opyright sebastian jensen / 2025 /

struct Entity;

struct Component
{
    Entity *owner;
    virtual void OnUpdate(float deltaTime) = 0;

    virtual ~Component() {};
};