#ifndef PLANTS_HPP
#define PLANTS_HPP

#include "../GameObject.hpp"
#include "GameWorld.hpp"

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
class Plant : public GameObject
{
public:
    Plant(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, pGameWorld gw) : GameObject(imageID, x, y, layer, width, height, animID), m_gw(gw) {}
    int isZombie()
    {
        return 0;
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
    // collision
    void collision()
    {
        SetHp(0);
    }

private:
    pGameWorld m_gw;
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

class Explosion : public GameObject
{
public:
    int isZombie()
    {
        return 3;
    }
    Explosion(int x, int y, pGameWorld gw) : GameObject(IMGID_EXPLOSION, x, y, LAYER_PROJECTILES, 3 * LAWN_GRID_WIDTH, 3 * LAWN_GRID_HEIGHT, ANIMID_NO_ANIMATION), m_gw(gw) {}
    void Update();
    void OnClick() {}
    // collision
    void collision() {}

private:
    pGameWorld m_gw;
    int bombtime = 3;
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