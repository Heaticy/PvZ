#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <list>
#include <memory>

#include "WorldBase.hpp"
#include "utils.hpp"

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
  int GetHand()
  {
    return m_hand;
  }
  void addCooldowndmask(int x, int y, int cdtime);

private:
  std::list<pGameObject> GameObjects;
  int m_hand = 0;
};

#endif // !GAMEWORLD_HPP__
