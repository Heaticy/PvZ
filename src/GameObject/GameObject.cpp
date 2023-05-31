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
}
void Seed::OnClick()
{
    if (!m_gw->GetShovel())
    {
        return;
    }
    if (m_gw->GetSun() < m_price)
    {
        return;
    }
    else
    {
        m_gw->addCooldowndmask(GetX(), GetY(), m_cd);
    }
}