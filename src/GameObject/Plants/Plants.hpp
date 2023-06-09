#ifndef PLANTS_HPP
#define PLANTS_HPP

#include "../GameObject.hpp"
#include "GameWorld.hpp"

class Plant : public GameObject
{
public:
    Plant(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, pGameWorld gw) : GameObject(imageID, x, y, layer, width, height, animID), m_gw(gw) {}
    int GetCategory()
    {
        return PLANT;
    }
    void OnClick();
    void collision()
    {
        SetHp(GetHp() - 3);
    }

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

class Wallnut : public Plant
{
public:
    Wallnut(int x, int y, pGameWorld gw) : Plant(IMGID_WALLNUT, x, y, LAYER_PLANTS, 60, 80, ANIMID_IDLE_ANIM, gw)
    {
        SetHp(4000);
    }
    void Update();
};

class CherryBomb : public Plant
{
public:
    CherryBomb(int x, int y, pGameWorld gw) : Plant(IMGID_CHERRY_BOMB, x, y, LAYER_PLANTS, 60, 80, ANIMID_IDLE_ANIM, gw)
    {
        SetHp(4000);
    }
    void Update();
    void OnClick() {}

private:
    int bombtime = 15;
};

class Repeater : public Plant
{
public:
    Repeater(int x, int y, pGameWorld gw) : Plant(IMGID_REPEATER, x, y, LAYER_PLANTS, 60, 80, ANIMID_IDLE_ANIM, gw)
    {
        SetHp(300);
    }
    void Update();

private:
    int shoottime = 0;
    int doubleshoot = -1;
};

#endif // PLANTS_HPP