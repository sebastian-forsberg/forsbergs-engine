#pragma once

// Game.h /////////////////////////
// F-25 ENGINE / Main entry point |___________________________________________.
//   This is the class that you extend to actually create your game           |
// The game also keeps a list of all entities, a system which in a bigger     |
// engine should probably be moved to a Scene or similair concept.            |
///////////////////////////////////////// (c)opyright sebastian jensen / 2025 /

#include "Common.h"

#include "./Collections/LinkedList.h"

#include "Entity.h"
#include "Logger.h"

struct Game
{
    Logger *logger;
    LinkedList<Entity *> entities;

    Game(int32_t width, int32_t height, const char *windowTitle)
    {
        logger = new Logger();
        InitWindow(width, height, windowTitle);
        logger->Log(INFO, "Game started");
    }

    void EnterMainLoop()
    {
        while (!WindowShouldClose())
        {
            f32 deltaTime = GetFrameTime();
            BeginDrawing();
            ClearBackground(BLACK);
            for (int i = 0; i < entities.Count(); i++)
            {
                auto e = entities.GetDataAt(i);
                if (e.valid)
                {
                    e.data->OnUpdate(deltaTime);
                }
            }
            Tick(deltaTime);
            EndDrawing();
        }
    }

    virtual void Tick(float deltaTime) {};

    ~Game()
    {
        logger->Log(INFO, "Game ended");
        delete logger;
    };
};