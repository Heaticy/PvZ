#include "Zombies.hpp"
#include "GameWorld.hpp"
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
    if (eatting == 1 && GetCurrentAnimation() == ANIMID_WALK_ANIM)
    {
        PlayAnimation(ANIMID_EAT_ANIM);
    }
    if (eatting == 0 && GetCurrentAnimation() == ANIMID_EAT_ANIM)
    {
        PlayAnimation(ANIMID_WALK_ANIM);
    }
    if (poleVaultingtime == -1)
    {
        // 暂时向左移动40
        MoveTo(GetX() - 40, GetY());
        for (auto &project : m_gw->Getlist())
        {
            if (project->isZombie() == 0)
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