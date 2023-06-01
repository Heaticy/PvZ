#ifndef SEEDS_HPP
#define SEEDS_HPP

#include "../GameObject.hpp"
#include "GameWorld.hpp"
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
    int GetCategory()
    {
        return SEED;
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
    int GetCategory()
    {
        return SEED;
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

#endif // SEEDS_HPP