#include "GameObject.hpp"
#include "GameWorld.hpp"
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
void Seed::OnClick()
{
    if (m_gw->GetHand())
    {
        return;
    }
    if (m_gw->GetSun() < m_price)
    {
        return;
    }
    else
    {
        m_gw->SetSun(m_gw->GetSun() - m_price);
        SetSeed();
        m_gw->addCooldowndmask(GetX(), GetY(), m_cd);
    }
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

    default:
        break;
    }
}

void Sunflower::Update()
{
    if (!suntimecorder)
    {
        m_gw->addobject(std::make_shared<Sun>(GetX(), GetY(), 0, m_gw));
        suntimecorder = 600;
    }
    suntimecorder -= 1;
}
void Sunflower::OnClick()
{
    if (m_gw->GetHand() == SHOVEL)
    {
        SetHp(0);
    }
}
void Shovel::OnClick()
{
    if (m_gw->GetHand() == SHOVEL)
    {
        m_gw->Sethand(NOTHING);
        return;
    }
    else if (m_gw->GetHand() == NOTHING)
    {
        SetSeed();
    }
    else
    {
        return;
    }
}
void SunflowerSeed::SetSeed()
{
    m_gw->Sethand(SUNFLOWERSEED);
}
void WallnutSeed::SetSeed()
{
    m_gw->Sethand(WALLNUTSEED);
}
void PeashooterSeed::SetSeed()
{
    m_gw->Sethand(PEASHOOTERSEED);
}
void CherryBombSeed::SetSeed()
{
    m_gw->Sethand(CHERRYBOMBSEED);
}
void RepeaterSeed::SetSeed()
{
    m_gw->Sethand(REPEATERSEED);
}
void Shovel::SetSeed()
{
    m_gw->Sethand(SHOVEL);
}