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
  GameObject(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID) : ObjectBase(imageID, x, y, layer, width, height, animID) {}
  GameObject(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, int hp) : ObjectBase(imageID, x, y, layer, width, height, animID), m_hp(hp) {}
  void SetHp(int hp)
  {
    m_hp = hp;
  }
  int GetHp()
  {
    return m_hp;
  }
  virtual int isZombie() = 0;

protected:
  int m_hp = 1;
};

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
  Sun(int x, int y, bool z, pGameWorld gw) : GameObject(IMGID_SUN, x, y, LAYER_SUN, 80, 80, ANIMID_IDLE_ANIM), m_isfromsky(z), m_gw(gw)
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
  void OnClick();
  void Update();
  int isZombie()
  {
    return -1;
  }

private:
  int m_falltime;
  bool m_isfromsky;
  pGameWorld m_gw;
};

class PlantingSpot : public GameObject
{
public:
  PlantingSpot(int x, int y) : GameObject(IMGID_NONE, x, y, LAYER_UI, 60, 80, ANIMID_NO_ANIMATION) {}
  void OnClick() {}
  void Update() {}
  int isZombie()
  {
    return -1;
  }
};

class CooldownMask : public GameObject
{
public:
  CooldownMask(int x, int y, int cdtime) : GameObject(IMGID_COOLDOWN_MASK, x, y, LAYER_COOLDOWN_MASK, 50, 70, ANIMID_NO_ANIMATION)
  {
    SetHp(cdtime);
  }
  void OnClick()
  {
  }
  void Update()
  {
    SetHp(GetHp() - 1);
  }
  int isZombie()
  {
    return -1;
  }
};

class Seed : public GameObject
{
private:
  int m_price;
  int m_cd;
  pGameWorld m_gw;

public:
  Seed(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, int price, int cd, pGameWorld gw) : GameObject(imageID, x, y, layer, width, height, animID), m_cd(cd), m_price(price), m_gw(gw) {}
  int isZombie()
  {
    return -1;
  }
  int Getprice()
  {
    return m_price;
  }
  void OnClick();
  void Update() {}
};

class SunflowerSeed : public Seed
{
public:
  SunflowerSeed(pGameWorld gw) : Seed(IMGID_SEED_SUNFLOWER, 130, WINDOW_HEIGHT - 44, LAYER_UI, 50, 70, ANIMID_NO_ANIMATION, 50, 240, gw) {}
};
#endif // !GAMEOBJECT_HPP__
