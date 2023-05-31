#include "GameWorld.hpp"
#include "GameObject.hpp"
GameWorld::GameWorld() {}

GameWorld::~GameWorld() {}

void GameWorld::Init()
{
  // YOUR CODE HERE

  SetWave(0);
  SetSun(50);
  // Create Planting Spot

  // Create Background
  addobject(std::make_shared<Background>());
}

LevelStatus GameWorld::Update()
{
  // YOUR CODE HERE
  return LevelStatus::ONGOING;
}

void GameWorld::CleanUp()
{
  // YOUR CODE HERE
  SetWave(0);
  SetSun(50);
}
