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
    if (!shoottime)
    {
        int flag = 1;
        for (auto &zombie : m_gw->Getlist())
        {
            if (zombie->isZombie() == 1)
            {
                if (zombie->GetY() == GetY())
                {
                    flag = 0;
                    break;
                }
            }
        }
        if (flag)
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
    if (!shoottime)
    {
        // if(noZomble)
        // return;
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

void Zombie::Update()
{
    if (!GetHp())
    {
        return;
    }
    if (eatting == 1 && GetCurrentAnimation() == ANIMID_WALK_ANIM)
    {
        PlayAnimation(ANIMID_EAT_ANIM);
    }
    if (eatting == 0 && GetCurrentAnimation() == ANIMID_EAT_ANIM)
    {
        PlayAnimation(ANIMID_WALK_ANIM);
    }
    if (GetCurrentAnimation() == ANIMID_WALK_ANIM)
    {
        MoveTo(GetX() - 1, GetY());
    }
}

void BucketHeadZombie::Update()
{
    if (!GetHp())
    {
        return;
    }
    if (GetCurrentAnimation() == ANIMID_WALK_ANIM)
    {
        MoveTo(GetX() - 1, GetY());
    }
    if (GetHp() <= 200)
    {
        ChangeImage(IMGID_REGULAR_ZOMBIE);
    }
}

void PoleVaultingZombie::Update()
{
    if (!GetHp())
    {
        return;
    }
    if (poleVaultingtime < 0)
    {
        // 暂时向左移动40
        MoveTo(GetX() - 40, GetY());
        for (auto &project : m_gw->Getlist())
        {
            if (project->isZombie() == -1)
            {
                int ax1 = project->GetX() + project->GetWidth() / 2;
                int ax2 = project->GetX() - project->GetWidth() / 2;
                int ay1 = project->GetY() + project->GetHeight() / 2;
                int ay2 = project->GetY() - project->GetHeight() / 2;

                int bx1 = GetX() + GetWidth() / 2;
                int bx2 = GetX() - GetWidth() / 2;
                int by1 = GetY() + GetHeight() / 2;
                int by2 = GetY() - GetHeight() / 2;

                // 检测碰撞
                if (ax1 > bx2 && ax2 < bx1 && ay1 > by2 && ay2 < by1)
                {
                    PlayAnimation(ANIMID_JUMP_ANIM);
                    poleVaultingtime = 42;
                }
            }
        }
        MoveTo(GetX() + 40, GetY());
    }
    else if (poleVaultingtime > 0)
    {
        poleVaultingtime -= 1;
    }
    else if (poleVaultingtime == 0)
    {
        MoveTo(GetX() - 150, GetY());
        PlayAnimation(ANIMID_WALK_ANIM);
        poleVaultingtime = -2;
    }
    if (GetCurrentAnimation() == ANIMID_RUN_ANIM)
    {
        MoveTo(GetX() - 2, GetY());
    }
    else if (GetCurrentAnimation() == ANIMID_WALK_ANIM)
    {
        MoveTo(GetX() - 1, GetY());
    }
}