#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <list>
#include <memory>

#include "WorldBase.hpp"
#include "utils.hpp"
#include "utils_new.hpp"

class GameObject;
using pGameObject = std::shared_ptr<GameObject>;
class GameWorld : public WorldBase, public std::enable_shared_from_this<GameWorld>
{
public:
  // Use shared_from_this() instead of "this".
  GameWorld();
  virtual ~GameWorld();

  void Init() override;

  LevelStatus Update() override;

  void CleanUp() override;

  void addobject(pGameObject object)
  {
    GameObjects.push_back(object);
  }
  void Sethand(int hand)
  {
    m_hand = hand;
  }
  int GetHand() const
  {
    return m_hand;
  }
  void addCooldowndmask(int x, int y, int cdtime);
  void UpdateObjects();
  void ClearDeadObjects();
  std::list<pGameObject> &Getlist()
  {
    return GameObjects;
  }

private:
  std::list<pGameObject> GameObjects;
  int m_hand = 0;
  int m_time = 0;
  int m_nextwave = 1200;
  int m_numZombie = 0;
};

#endif // !GAMEWORLD_HPP__
