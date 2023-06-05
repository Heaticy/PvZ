#include "Plants.hpp"
#include "GameWorld.hpp"
#include "FlyingObject.hpp"

void Sun::OnClick()
{
    m_gw->SetSun(m_gw->GetSun() + 25);
    SetHp(0);
}
void Sun::Update()
{
    if (m_falltime > 0)
    {
        if (m_isfromsky)
        {
            MoveTo(GetX(), GetY() - 2);
        }
        else
        {
            MoveTo(GetX() - 1, GetY() + 4 - (12 - m_falltime));
        }
    }
    if (m_falltime < -300)
    {
        SetHp(0);
    }
    m_falltime -= 1;
}
void PlantingSpot::OnClick()
{
    switch (m_gw->GetHand())
    {
    case NOTHING:
        break;
    case SUNFLOWERSEED:
        m_gw->addobject(std::make_shared<Sunflower>(GetX(), GetY(), m_gw));
        m_gw->Sethand(NOTHING);
        break;
    case PEASHOOTERSEED:
        m_gw->addobject(std::make_shared<Peashooter>(GetX(), GetY(), m_gw));
        m_gw->Sethand(NOTHING);
        break;
    case WALLNUTSEED:
        m_gw->addobject(std::make_shared<Wallnut>(GetX(), GetY(), m_gw));
        m_gw->Sethand(NOTHING);
        break;
    case CHERRYBOMBSEED:
        m_gw->addobject(std::make_shared<CherryBomb>(GetX(), GetY(), m_gw));
        m_gw->Sethand(NOTHING);
        break;
    case REPEATERSEED:
        m_gw->addobject(std::make_shared<Repeater>(GetX(), GetY(), m_gw));
        m_gw->Sethand(NOTHING);
        break;
    default:
        break;
    }
}

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
        NoZombieOnRight = 1;
        for (auto &zombie : m_gw->Getlist())
        {
            if (zombie->GetCategory() == ZOMBIE)
            {
                if (zombie->GetY() == GetY() && zombie->GetX() > GetX())
                {
                    NoZombieOnRight = 0;
                    break;
                }
            }
        }
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

        NoZombieOnRight = 1;
        for (auto &zombie : m_gw->Getlist())
        {
            if (zombie->GetCategory() == ZOMBIE)
            {
                if (zombie->GetY() == GetY() && zombie->GetX() > GetX())
                {
                    NoZombieOnRight = 0;
                    break;
                }
            }
        }
        if (NoZombieOnRight)
        {
            return;
        }
        if (doubleshoot == -1)
        {
            m_gw->addobject(std::make_shared<Pea>(GetX() + 30, GetY() + 20, m_gw));
            doubleshoot = 5;
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
