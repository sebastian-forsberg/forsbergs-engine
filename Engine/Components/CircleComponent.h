#pragma once

#include "../Common.h"
#include "../Component.h"
#include "../Entity.h"

struct CircleComponent : public Component
{
    i32 radius;
    Color color;

    void OnUpdate(float deltaTime) override
    {
        DrawCircle(
            owner->position.x, owner->position.y, radius, color);
    }

    CircleComponent(i32 radius, Color color) : radius{radius}, color{color} {}
};