#pragma once

#include "../Common.h"
#include "../Component.h"
#include "../Entity.h"

struct RectangleComponent : public Component
{
    i32 width;
    i32 height;
    Color color;

    void OnUpdate(float deltaTime) override
    {
        Rectangle finalRect = {
            owner->position.x - width / 2,
            owner->position.y - height / 2,
            (f32)width, (f32)height};
        DrawRectangleRec(finalRect, color);
    }
};