#include "Plants.hpp"
#include "GameWorld.hpp"
#include "FlyingObject.hpp"
#include "Environments.hpp"
void Plant::OnClick()
{
    if (m_gw->GetHand() == SHOVEL)
    {
        SetHp(0);
        m_gw->Sethand(NOTHING);
    }
}

void Sunflower::Update()
{
    if (!GetHp())
    {
        return;
    }
    if (!suntimecorder)
    {
        m_gw->addobject(std::make_shared<Sun>(GetX(), GetY(), 0, m_gw));
        suntimecorder = 600;
    }
    suntimecorder -= 1;
}

void Peashooter::Update()
{
    if (!GetHp())
    {
        return;
    }
    static int NoZombieOnRight = 1;
    if (!shoottime)
    {
        NoZombieOnRight = m_gw->JudgeNoZombieOnTheRight(shared_from_this());
        if (NoZombieOnRight)
        {
            return;
        }
        m_gw->addobject(std::make_shared<Pea>(GetX() + 30, GetY() + 20, m_gw));
        shoottime = 30;
    }
    else
    {
        shoottime -= 1;
    }
}

void Repeater::Update()
{
    if (!GetHp())
    {
        return;
    }
    static int NoZombieOnRight = 1;
    if (!shoottime)
    {
        NoZombieOnRight = m_gw->JudgeNoZombieOnTheRight(shared_from_this());
        if (NoZombieOnRight)
        {
            return;
        }
        if (doubleshoot == -1)
        {
            m_gw->addobject(std::make_shared<Pea>(GetX() + 30, GetY() + 20, m_gw));
            doubleshoot = 4;
            return;
        }
        else if (doubleshoot > 0)
        {
            doubleshoot -= 1;
            return;
        }
        else
        {
            m_gw->addobject(std::make_shared<Pea>(GetX() + 30, GetY() + 20, m_gw));
            shoottime = 25;
            doubleshoot = -1;
            return;
        }
    }
    else
    {
        shoottime -= 1;
    }
}

void Wallnut::Update()
{
    if (!GetHp())
    {
        return;
    }
    else if (GetHp() < 4000 / 3)
    {
        ChangeImage(IMGID_WALLNUT_CRACKED);
    }
}

void CherryBomb::Update()
{
    if (!GetHp())
    {
        return;
    }
    if (!bombtime)
    {
        m_gw->addobject(std::make_shared<Explosion>(GetX(), GetY(), m_gw));
        SetHp(0);
    }
    else
    {
        bombtime -= 1;
    }
}
