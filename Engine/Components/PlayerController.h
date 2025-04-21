#pragma once

#include "../Common.h"
#include "../Component.h"
#include "../Entity.h"

struct PlayerController : public Component
{
    float movementSpeed; // pixels per second

    void OnUpdate(float deltaTime) override
    {
        Vector2 direction{0.0f, 0.0f};

        if (IsKeyDown(KEY_W))
        {
            direction.y = -1.0f;
        }
        else if (IsKeyDown(KEY_S))
        {
            direction.y = 1.0f;
        }

        if (IsKeyDown(KEY_A))
        {
            direction.x = -1.0f;
        }
        else if (IsKeyDown(KEY_D))
        {
            direction.x = 1.0f;
        }

        Vector2 velocity = Vector2Scale(Vector2Normalize(direction), movementSpeed * deltaTime);
        owner->position = Vector2Add(owner->position, velocity);
    }

    PlayerController(float movementSpeed) : movementSpeed{movementSpeed} {}
};