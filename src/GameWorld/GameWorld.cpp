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
  for (size_t i = 0; i != 5; i++)
  {
    for (size_t j = 0; j != 9; j++)
    {
      addobject(std::make_shared<PlantingSpot>(FIRST_COL_CENTER + j * LAWN_GRID_WIDTH, FIRST_ROW_CENTER + i * LAWN_GRID_HEIGHT));
    }
  }
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
