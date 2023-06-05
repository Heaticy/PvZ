#include "FlyingObject.hpp"

void Pea::Update()
{
    if (!GetHp())
    {
        return;
    }
    MoveTo(GetX() + 8, GetY());
    if (GetX() >= WINDOW_WIDTH)
    {
        SetHp(0);
    }
}
void Explosion::Update()
{
    if (!GetHp())
    {
        return;
    }
    if (!bombtime)
    {
        SetHp(0);
    }
    else
    {
        bombtime -= 1;
    }
}