#include "./Engine/Game.h"
#include "./Engine/ProfileTimer.h"

#include "./Engine/Collections/LinkedList.h"
#include "./Engine/Collections/DynArray.h"

#include "./Engine/Entity.h"
#include "./Engine/Component.h"

#include "./Engine/Components/CircleComponent.h"
#include "./Engine/Components/RectangleComponent.h"
#include "./Engine/Components/PlayerController.h"

struct MyGame : public Game
{

  Entity player;

  MyGame(int32_t width, int32_t height, const char *title) : Game(width, height, title)
  {
    player.active = true;
    player.position = Vector2{(f32)width / 2, (f32)height / 2};
    player.AddComponent<CircleComponent>(32, WHITE);
    player.AddComponent<PlayerController>(100);
    entities.InsertLast(&player);
  }

  void Tick(float deltaTime) override
  {
    DrawText("Game engine", 8, 8, 16, WHITE);
  }
};

bool tests(const Game &game)
{
  // Testing profiler
  {
    ProfileTimer timer{game.logger, "Profiler Test"};
    uint64_t sum = 0;
    for (uint64_t itr = 0; itr < 1000000; itr++)
    {
      sum += itr % 100; // useless busywork
    }
  }

  // Testing linked lists
  {
    game.logger->Log(TRACE, "Linked list test:");
    ProfileTimer timer{game.logger, "Linked List Test"};
    LinkedList<int> testList;
    testList.InsertLast(1);
    testList.InsertLast(4);
    testList.InsertAfter(2, testList.GetIndexOf(1));
    testList.InsertBefore(3, testList.GetIndexOf(4));
    testList.InsertFirst(0);
    testList.InsertLast(5);

    // Remove first:
    {
      testList.InsertFirst(666);
      int32_t test = testList.RemoveFirst().data;
      char msg[64];
      snprintf(msg, 64, "Removed value %d from beginning of list (should be 666)", test);
      game.logger->Log(TRACE, msg);
    }

    // Remove last:
    {
      testList.InsertLast(999);
      int32_t test = testList.RemoveLast().data;
      char msg[64];
      snprintf(msg, 64, "Removed value %d from beginning of list (should be 999)", test);
      game.logger->Log(TRACE, msg);
    }

    // Linked list iteration:
    for (int i = 0; i < testList.Count(); i++)
    {
      char msg[64];
      snprintf(msg, 64, "%d", testList.GetDataAt(i).data);
      game.logger->Log(TRACE, msg);
    }

    game.logger->Log(TRACE, "End of linked list test");
  }

  // Testing Dynamic Arrays
  {
    game.logger->Log(TRACE, "Dynamic array test:");
    ProfileTimer timer{game.logger, "Dynamic Array Tests"};
    DynArray<int> testArray{8};
    testArray.InsertFirst(5);
    testArray.InsertFirst(4);
    testArray.InsertFirst(3);
    testArray.InsertFirst(2);
    testArray.InsertFirst(1);
    testArray.InsertLast(6);
    testArray.InsertLast(7);
    testArray.InsertLast(8);
    testArray.InsertLast(9);
    testArray.InsertFirst(0);
    testArray.InsertAt(6, testArray.GetIndexOf(6));
    testArray.InsertAt(6, testArray.GetIndexOf(6));
    testArray.InsertAt(9, testArray.GetIndexOf(9));
    testArray.InsertAt(9, testArray.GetIndexOf(9));
    testArray.InsertLast(10);
    testArray.InsertFirst(-1);
    testArray.RemoveLast();
    testArray.RemoveFirst();

    for (int i = 0; i < testArray.Count(); i++)
    {
      char msg[64];
      snprintf(msg, 64, "%d", testArray.GetDataAt(i).data);
      game.logger->Log(TRACE, msg);
    }

    // Count and clear
    {
      char msg[64];
      snprintf(msg, 64, "Count: %d", testArray.Count());
      game.logger->Log(TRACE, msg);
      testArray.Clear();
      snprintf(msg, 64, "Count: %d", testArray.Count());
      game.logger->Log(TRACE, msg);
    }

    // Insert first, insert last
    {
      for (int i = 0; i < 10; i++)
      {
        testArray.InsertFirst(i + 100); // Horribly slow!
      }

      for (int i = 0; i < 10; i++)
      {
        testArray.InsertLast(i + 100); // Horribly slow!
      }

      for (int i = 0; i < testArray.Count(); i++)
      {
        char msg[64];
        snprintf(msg, 64, "%d", testArray.GetDataAt(i).data);
        game.logger->Log(TRACE, msg);
      }
    }

    game.logger->Log(TRACE, "End of dynamic array test");
  }

  return true;
}

int main()
{

  MyGame myGame{1024, 768, "Forsbergs Engine Alpha 0.001"};

  tests(myGame);

  myGame.EnterMainLoop();
  return 0;
}
