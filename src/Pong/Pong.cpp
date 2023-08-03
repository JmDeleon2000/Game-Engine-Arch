#include <print.h>

#include "Pong.h"
#include "Systems.h"

#include "ECS/Entity.h"

Pong::Pong(const char* name, int width, int height)
  : Game(name, width, height)
{
  Scene* gameplayScene = createGameplayScene();
  setScene(gameplayScene);
}

Pong::~Pong() {
  
}

Scene* Pong::createGameplayScene() {
  Scene* scene = new Scene("GAMEPLAY SCENE");

  Entity ball = scene->createEntity("BALL", 10, 10);
  ball.addComponent<SizeComponent>(20, 20);
  ball.addComponent<SpeedComponent>(200, 200);
  ball.addComponent<ColliderComponent>(false, 0);

  Entity paddle = scene->createEntity("PLAYER 1", 21, (screen_height / 2) - 50);
  paddle.addComponent<SizeComponent>(20, 100);
  paddle.addComponent<SpeedComponent>(0, 0);
  paddle.addComponent<Player1Component>(200);

  Entity paddle2 = scene->createEntity("PLAYER 2", screen_width - 21, (screen_height / 2) - 50);
  paddle2.addComponent<SizeComponent>(20, 100);
  paddle2.addComponent<SpeedComponent>(0, 0);
  paddle2.addComponent<Player2Component>(200);

  
  scene->addSetupSystem(new HelloWorldSystem());
  scene->addRenderSystem(new RectRenderSystem());
  scene->addUpdateSystem(new BounceUpdateSystem());
  scene->addUpdateSystem(new MovementUpdateSystem(screen_width, screen_height));
  scene->addEventSystem(new Player1InputSystem());
  scene->addEventSystem(new Player2InputSystem());

  scene->addUpdateSystem(new CollisionDetectionUpdateSystem());

  return scene;
}