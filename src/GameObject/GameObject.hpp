#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

#include <memory>
#include "ObjectBase.hpp"
#include <random>

class Random
{
private:
  std::random_device rd;
  std::mt19937 generator;
  std::uniform_int_distribution<int> distribution;

public:
  Random() : generator(rd()), distribution(63, 263) {}

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
  GameObject(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID) : ObjectBase(imageID, x, y, layer, width, height, animID)
  {
  }
  GameObject(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, int hp) : ObjectBase(imageID, x, y, layer, width, height, animID), m_hp(hp)
  {
  }
  void SetHp(int hp)
  {
    m_hp = hp;
  }

  virtual int isZombie() = 0;

protected:
  int m_hp = 1;
};

using pGameObject = std::shared_ptr<GameObject>;

class Background : public GameObject
{
public:
  Background() : GameObject(IMGID_BACKGROUND, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LAYER_BACKGROUND, WINDOW_WIDTH, WINDOW_HEIGHT, ANIMID_NO_ANIMATION) {}
  void OnClick() {}
  void Update() {}
  int isZombie()
  {
    return -1;
  }
};

class Sun : public GameObject
{
public:
  Sun(int x, int y, bool z) : GameObject(IMGID_SUN, x, y, LAYER_SUN, 80, 80, ANIMID_IDLE_ANIM), m_isfromsky(z)
  {
    if (z)
    {
      Random random;
      m_falltime = random.generateRandomNumber();
    }
    else
    {
      m_falltime = 12;
    }
  }
  void OnClick()
  {
    SetHp(-2500);
  }
  void Update()
  {
    if (m_falltime > 0)
    {
      if (m_isfromsky)
      {
        MoveTo(GetX(), GetY() - 2);
      }
      else
      {
        MoveTo(GetX() - 1, GetY() + 4 - (12 - m_falltime));
      }
    }
    if (m_falltime < -300)
    {
      SetHp(0);
    }
  }
  int isZombie()
  {
    return -1;
  }

private:
  int m_falltime;
  bool m_isfromsky;
};

class PlantingSpot : public GameObject
{
public:
  PlantingSpot(int x, int y) : GameObject(IMGID_WALLNUT, x, y, LAYER_UI, 60, 80, ANIMID_NO_ANIMATION) {}
  void OnClick() {}
  void Update() {}
  int isZombie()
  {
    return -1;
  }
};
#endif // !GAMEOBJECT_HPP__
