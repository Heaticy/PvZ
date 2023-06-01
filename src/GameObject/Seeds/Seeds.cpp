#include "Seeds.hpp"

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