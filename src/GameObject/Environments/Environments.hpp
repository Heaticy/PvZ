#ifndef ENVIRONMENTS_HPP__
#define ENVIRONMENTS_HPP__

#include "../GameObject.hpp"

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

#endif // !GAMEOBJECT_HPP__