#include "Environments.hpp"
#include "GameWorld.hpp"
#include "Plants.hpp"
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