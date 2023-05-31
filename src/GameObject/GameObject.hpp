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
  PlantingSpot(int x, int y, pGameWorld gw) : GameObject(IMGID_NONE, x, y, LAYER_UI, 60, 80, ANIMID_NO_ANIMATION), m_gw(gw) {}
  void OnClick();
  void Update() {}
  int isZombie()
  {
    return -1;
  }

private:
  pGameWorld m_gw;
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

protected:
  pGameWorld m_gw;

public:
  Seed(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, int price, int cd, pGameWorld gw) : GameObject(imageID, x, y, layer, width, height, animID), m_cd(cd), m_price(price), m_gw(gw) {}
  int isZombie()
  {
    return -1;
  }
  int Getprice() const
  {
    return m_price;
  }
  void OnClick();
  void Update() {}
  virtual void SetSeed() = 0;
};

class SunflowerSeed : public Seed
{
public:
  SunflowerSeed(pGameWorld gw) : Seed(IMGID_SEED_SUNFLOWER, 130, WINDOW_HEIGHT - 44, LAYER_UI, 50, 70, ANIMID_NO_ANIMATION, 50, 240, gw) {}
  void SetSeed();
};

class PeashooterSeed : public Seed
{
public:
  PeashooterSeed(pGameWorld gw) : Seed(IMGID_SEED_PEASHOOTER, 190, WINDOW_HEIGHT - 44, LAYER_UI, 50, 70, ANIMID_NO_ANIMATION, 100, 240, gw) {}
  void SetSeed();
};
class WallnutSeed : public Seed
{
public:
  WallnutSeed(pGameWorld gw) : Seed(IMGID_SEED_WALLNUT, 250, WINDOW_HEIGHT - 44, LAYER_UI, 50, 70, ANIMID_NO_ANIMATION, 50, 900, gw) {}
  void SetSeed();
};

class CherryBombSeed : public Seed
{
public:
  CherryBombSeed(pGameWorld gw) : Seed(IMGID_SEED_CHERRY_BOMB, 310, WINDOW_HEIGHT - 44, LAYER_UI, 50, 70, ANIMID_NO_ANIMATION, 150, 1200, gw) {}
  void SetSeed();
};

class RepeaterSeed : public Seed
{
public:
  RepeaterSeed(pGameWorld gw) : Seed(IMGID_SEED_REPEATER, 370, WINDOW_HEIGHT - 44, LAYER_UI, 50, 70, ANIMID_NO_ANIMATION, 200, 240, gw) {}
  void SetSeed();
};
class Shovel : public Seed
{
public:
  Shovel(pGameWorld gw) : Seed(IMGID_SHOVEL, 600, WINDOW_HEIGHT - 40, LAYER_UI, 50, 50, ANIMID_NO_ANIMATION, 0, 0, gw){};
  void OnClick();
  void SetSeed();
};

class Plant : public GameObject
{
public:
  Plant(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, pGameWorld gw) : GameObject(imageID, x, y, layer, width, height, animID), m_gw(gw) {}
  int isZombie()
  {
    return 0;
  }
  void OnClick();

protected:
  pGameWorld m_gw;
};

class Sunflower : public Plant
{
public:
  Sunflower(int x, int y, pGameWorld gw) : Plant(IMGID_SUNFLOWER, x, y, LAYER_PLANTS, 60, 80, ANIMID_IDLE_ANIM, gw)
  {
    SetHp(300);
    Random suntime(30, 600);
    suntimecorder = suntime.generateRandomNumber();
  }
  void Update();

private:
  int suntimecorder;
};

class Peashooter : public Plant
{
public:
  Peashooter(int x, int y, pGameWorld gw) : Plant(IMGID_PEASHOOTER, x, y, LAYER_PLANTS, 60, 80, ANIMID_IDLE_ANIM, gw)
  {
    SetHp(300);
  }
  void Update();

private:
  int shoottime = 0;
};

class Pea : public GameObject
{
public:
  int isZombie()
  {
    return 2;
  }
  Pea(int x, int y, pGameWorld gw) : GameObject(IMGID_PEA, x, y, LAYER_PROJECTILES, 28, 28, ANIMID_NO_ANIMATION), m_gw(gw) {}
  void Update();
  void OnClick() {}

private:
  pGameWorld m_gw;
};

#endif // !GAMEOBJECT_HPP__