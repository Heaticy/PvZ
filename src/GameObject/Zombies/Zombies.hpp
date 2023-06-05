#ifndef ZOMBIES_HPP
#define ZOMBIES_HPP

#include "../GameObject.hpp"

class Zombie : public GameObject
{
public:
    Zombie(int x, int y, pGameWorld gw, AnimID animID) : GameObject(IMGID_REGULAR_ZOMBIE, x, y, LAYER_ZOMBIES, 20, 80, animID), m_gw(gw) {}
    void OnClick(){};
    int GetCategory()
    {
        return ZOMBIE;
    }
    void Update();
    void collision(int damage)
    {
        SetHp(GetHp() - damage);
    }
    void collision()
    {
        eatting = 1;
    }
    void noeat()
    {
        eatting = 0;
    }
    void explosion()
    {
        SetHp(0);
    }

protected:
    pGameWorld m_gw;
    int eatting = 0;
};

class RegularZombie : public Zombie
{
public:
    RegularZombie(int x, int y, pGameWorld gw) : Zombie(x, y, gw, ANIMID_WALK_ANIM)
    {
        SetHp(200);
    }
};

class BucketHeadZombie : public Zombie
{
public:
    BucketHeadZombie(int x, int y, pGameWorld gw) : Zombie(x, y, gw, ANIMID_WALK_ANIM)
    {
        SetHp(1300);
        ChangeImage(IMGID_BUCKET_HEAD_ZOMBIE);
    }
    void Update();
};

class PoleVaultingZombie : public Zombie
{
public:
    PoleVaultingZombie(int x, int y, pGameWorld gw) : Zombie(x, y, gw, ANIMID_RUN_ANIM)
    {
        SetHp(340);
        ChangeImage(IMGID_POLE_VAULTING_ZOMBIE);
    }
    void Update();
    void SetPoleVaultingtime(int time)
    {
        poleVaultingtime = time;
    }

private:
    int poleVaultingtime = -1;
};

#endif // ZOMBIES_HPP