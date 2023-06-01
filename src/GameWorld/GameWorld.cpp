#include "GameWorld.hpp"
#include "GameObject.hpp"
GameWorld::GameWorld() {}

GameWorld::~GameWorld() {}

void GameWorld::Init()
{
  // YOUR CODE HERE

  SetWave(0);
  SetSun(5000);
  // Create Planting Spot
  for (size_t i = 0; i != 5; i++)
  {
    for (size_t j = 0; j != 9; j++)
    {
      addobject(std::make_shared<PlantingSpot>(FIRST_COL_CENTER + j * LAWN_GRID_WIDTH, FIRST_ROW_CENTER + i * LAWN_GRID_HEIGHT, shared_from_this()));
    }
  }
  // Create Background
  addobject(std::make_shared<Background>());

  // Create seeds
  addobject(std::make_shared<SunflowerSeed>(shared_from_this()));
  addobject(std::make_shared<PeashooterSeed>(shared_from_this()));
  addobject(std::make_shared<WallnutSeed>(shared_from_this()));
  addobject(std::make_shared<CherryBombSeed>(shared_from_this()));
  addobject(std::make_shared<RepeaterSeed>(shared_from_this()));
  addobject(std::make_shared<Shovel>(shared_from_this()));
}
void GameWorld::UpdateObjects()
{
  for (auto &object : GameObjects)
  {
    object->Update();
  }
}
void GameWorld::ClearDeadObjects()
{
  for (auto it = GameObjects.begin(); it != GameObjects.end();)
  {
    if ((*it)->GetHp() <= 0)
    {
      it = GameObjects.erase(it); // 删除对象并更新迭代器
    }
    else
    {
      ++it; // 移动到下一个对象
    }
  }
}

double generateRandomFloat()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);

  return dis(gen);
}
LevelStatus GameWorld::Update()
{
  // YOUR CODE HERE
  m_time += 1;
  if ((m_time - 180) % 300 == 0)
  {
    Random ran(75, WINDOW_WIDTH - 75);
    addobject(std::make_shared<Sun>(ran.generateRandomNumber(), WINDOW_HEIGHT - 1, 1, shared_from_this()));
  }
  if (!m_nextwave)
  {
    m_numZombie = (15 + GetWave()) / 10;
    m_nextwave = std::max(150, 600 - 20 * GetWave());
    SetWave(GetWave() + 1);
  }

  if (m_numZombie > 0)
  {
    int P1 = 20;
    int P2 = 2 * std::max(GetWave() - 8, 0);
    int P3 = 3 * std::max(GetWave() - 15, 0);
    int totalProbability = P1 + P2 + P3;

    double normalZombieProbability = static_cast<double>(P1) / totalProbability;
    double poleVaultingZombieProbability = static_cast<double>(P2) / totalProbability;
    double bucketheadZombieProbability = static_cast<double>(P3) / totalProbability;
    Random generateRow(0, 4);
    Random generateX(WINDOW_WIDTH - 40, WINDOW_WIDTH - 1);

    while (m_numZombie)
    {
      double randomFloat = generateRandomFloat();
      int randomRownumber = generateRow.generateRandomNumber();
      int randomXnumber = generateX.generateRandomNumber();
      if (randomFloat <= normalZombieProbability)
      {
        addobject(std::make_shared<RegularZombie>(randomXnumber, FIRST_ROW_CENTER + randomRownumber * LAWN_GRID_HEIGHT, shared_from_this()));
      }
      else if (randomFloat <= normalZombieProbability + poleVaultingZombieProbability)
      {
        addobject(std::make_shared<PoleVaultingZombie>(randomXnumber, FIRST_ROW_CENTER + randomRownumber * LAWN_GRID_HEIGHT, shared_from_this()));
      }
      else
      {
        addobject(std::make_shared<BucketHeadZombie>(randomXnumber, FIRST_ROW_CENTER + randomRownumber * LAWN_GRID_HEIGHT, shared_from_this()));
      }
      m_numZombie -= 1;
    }
  }
  UpdateObjects();
  ClearDeadObjects();
  return LevelStatus::ONGOING;
}

void GameWorld::CleanUp()
{
  // YOUR CODE HERE
  SetWave(0);
  SetSun(50);
}
void GameWorld::addCooldowndmask(int x, int y, int cdtime)
{
  addobject(std::make_shared<CooldownMask>(x, y, cdtime));
}