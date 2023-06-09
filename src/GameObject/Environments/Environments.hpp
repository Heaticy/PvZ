#ifndef ENVIRONMENTS_HPP__
#define ENVIRONMENTS_HPP__

#include "../GameObject.hpp"

class Background : public GameObject
{
public:
    Background() : GameObject(IMGID_BACKGROUND, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LAYER_BACKGROUND, WINDOW_WIDTH, WINDOW_HEIGHT, ANIMID_NO_ANIMATION) {}
    void OnClick() {}
    void Update() {}
    int GetCategory()
    {
        return ENVIRONMENT;
    }
};
class PlantingSpot : public GameObject
{
public:
    PlantingSpot(int x, int y, pGameWorld gw) : GameObject(IMGID_NONE, x, y, LAYER_UI, 60, 80, ANIMID_NO_ANIMATION), m_gw(gw) {}
    void OnClick();
    void Update() {}
    int GetCategory()
    {
        return ENVIRONMENT;
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
    int GetCategory()
    {
        return ENVIRONMENT;
    }

private:
    int m_falltime;
    bool m_isfromsky;
    pGameWorld m_gw;
};
#endif // !GAMEOBJECT_HPP__