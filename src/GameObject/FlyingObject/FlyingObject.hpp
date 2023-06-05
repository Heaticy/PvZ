#ifndef FLYOBJECT_HPP
#define FLYOBJECT_HPP
#include "../GameObject.hpp"
#include "GameWorld.hpp"

class FlyingObject : public GameObject
{
public:
    FlyingObject(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID) : GameObject(imageID, x, y, layer, width, height, animID) {}
    int GetCategory()
    {
        return FLYINGOBJECT;
    }
    void OnClick() {}
    int GetDamage()
    {
        return m_damage;
    }

protected:
    int m_damage;
};

class Explosion : public FlyingObject
{
public:
    Explosion(int x, int y, pGameWorld gw) : FlyingObject(IMGID_EXPLOSION, x, y, LAYER_PROJECTILES, 3 * LAWN_GRID_WIDTH, 3 * LAWN_GRID_HEIGHT, ANIMID_NO_ANIMATION), m_gw(gw) { m_damage = 2000; }
    void Update();

    // collision
    void collision() {}

private:
    pGameWorld m_gw;
    int bombtime = 3;
};

class Pea : public FlyingObject
{
public:
    Pea(int x, int y, pGameWorld gw) : FlyingObject(IMGID_PEA, x, y, LAYER_PROJECTILES, 28, 28, ANIMID_NO_ANIMATION), m_gw(gw) { m_damage = 20; }
    void Update();
    // collision
    void collision()
    {
        SetHp(0);
    }

private:
    pGameWorld m_gw;
};

#endif // FLYOBJECT_HPP