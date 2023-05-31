#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <list>
#include <memory>

#include "WorldBase.hpp"
#include "utils.hpp"
#include "GameObject.hpp"
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

private:
  std::list<pGameObject> GameObjects;
};

#endif // !GAMEWORLD_HPP__
