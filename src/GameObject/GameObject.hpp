#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

#include <memory>
#include <random>

#include "ObjectBase.hpp"

class Random
{
private:
  std::random_device rd;
  std::mt19937 generator;
  std::uniform_int_distribution<int> distribution;

public:
  Random() : generator(rd()), distribution(63, 263) {}
  Random(int x, int y) : generator(rd()), distribution(x, y) {}
  int generateRandomNumber()
  {
    return distribution(generator);
  }
};

// Declares the class name GameWorld so that its pointers can be used.
class GameWorld;
using pGameWorld = std::shared_ptr<GameWorld>;

class GameObject : public ObjectBase, public std::enable_shared_from_this<GameObject>
{
public:
  using std::enable_shared_from_this<GameObject>::shared_from_this; // Use shared_from_this() instead of "this".
  GameObject(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID) : ObjectBase(imageID, x, y, layer, width, height, animID) {}
  GameObject(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, int hp) : ObjectBase(imageID, x, y, layer, width, height, animID), m_hp(hp) {}
  void SetHp(int hp)
  {
    m_hp = hp;
  }
  int GetHp() const
  {
    return m_hp;
  }
  virtual int GetCategory() = 0;
  virtual void collision() {}
  virtual void collision(int) {}
  virtual void explosion() {}
  virtual void noeat() {}

protected:
  int m_hp = 1;
};

#endif // !GAMEOBJECT_HPP__
