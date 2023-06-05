#ifndef FLYOBJECT_HPP
#define FLYOBJECT_HPP
#include "../GameObject.hpp"
#include "GameWorld.hpp"

class Explosion : public GameObject
{
public:
    int GetCategory()
    {
        return EXPLOSION;
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

class Pea : public GameObject
{
public:
    int GetCategory()
    {
        return PEA;
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

#endif // FLYOBJECT_HPP