#pragma once

#include "Axiom/Experimental/Game/GameContext.hpp"

#include <cstdlib>

namespace Axiom {

class EnemySystem
{
public:
    void update(GameContext& ctx)
    {
        timer += ctx.dt;

        switch (ctx.enemyState)
        {
        case EnemyState::Hidden:
            updateHidden(ctx);
            break;

        case EnemyState::Camera2:
            updateCamera2(ctx);
            break;

        case EnemyState::Camera1:
            updateCamera1(ctx);
            break;

        case EnemyState::OfficeFar:
            updateOfficeFar(ctx);
            break;

        case EnemyState::OfficeClose:
            updateOfficeClose(ctx);
            break;

        case EnemyState::Idle:
            updateIdle(ctx);
            break;

        case EnemyState::Watching:
            updateWatching(ctx);
            break;

        case EnemyState::Approaching:
            updateApproaching(ctx);
            break;

        case EnemyState::Attack:
            updateAttack(ctx);
            break;

        default:
            break;
        }

        debugStateChange(ctx);
    }

private:
    float timer = 0.0f;

    float hiddenTime = 2.0f;
    float camera2Time = 3.0f;
    float camera1Time = 3.0f;
    float officeFarTime = 3.0f;

    float idleTime = 2.0f;
    float watchingTime = 3.0f;
    float approachTime = 2.0f;

    int aggression = 1;

    int cameraChance = 10;
    int normalChance = 40;
    int lowPowerBonus = 20;

    void changeState(GameContext& ctx, EnemyState newState)
    {
        timer = 0.0f;
        ctx.enemyState = newState;
    }

    void updateHidden(GameContext& ctx)
    {
        if (timer > hiddenTime)
            changeState(ctx, EnemyState::Camera2);
    }

    void updateCamera2(GameContext& ctx)
    {
        if (timer > camera2Time)
            changeState(ctx, EnemyState::Camera1);
    }

    void updateCamera1(GameContext& ctx)
    {
        if (timer > camera1Time)
            changeState(ctx, EnemyState::OfficeFar);
    }

    void updateOfficeFar(GameContext& ctx)
    {
        if (timer > officeFarTime)
            changeState(ctx, EnemyState::OfficeClose);
    }

    void updateOfficeClose(GameContext& ctx)
    {
        if (!ctx.doorClosed)
        {
            changeState(ctx, EnemyState::Attack);
            return;
        }

        if (timer > 2.0f)
        {
            changeState(ctx, EnemyState::Camera1);
        }
    }

    void updateIdle(GameContext& ctx)
    {
        if (timer > idleTime && randomChance(ctx))
            changeState(ctx, EnemyState::Watching);
    }

    EnemyState lastDebugState = EnemyState::Hidden;

    void debugStateChange(GameContext& ctx)
    {
        if (ctx.enemyState == lastDebugState)
        return;

        lastDebugState = ctx.enemyState;
    }

    void updateWatching(GameContext& ctx)
    {
        if (!ctx.cameraOn && timer > watchingTime)
            changeState(ctx, EnemyState::Approaching);
    }

    void updateApproaching(GameContext& ctx)
    {
        if (ctx.cameraOn)
            changeState(ctx, EnemyState::Watching);

        if (timer > approachTime)
            changeState(ctx, EnemyState::Attack);
    }

    void updateAttack(GameContext& ctx)
    {
        if (!ctx.doorClosed)
            ctx.gameOver = true;
        else
            changeState(ctx, EnemyState::Watching);
    }

    bool randomChance(GameContext& ctx)
    {
        int chance = ctx.cameraOn ? cameraChance : normalChance;

        chance += aggression * 5;

        chance += (ctx.night - 1) * 5;

        switch (ctx.difficulty)
        {
            case Difficulty::Easy:
            chance += 5;
            break;

            case Difficulty::Normal:
            chance += 15;
            break;

            case Difficulty::Hard:
            chance += 25;
            break;
        }

        if (chance < 0)
        chance = 0;

        if (chance > 90)
        chance = 90;
        
        if (ctx.power < 20)
        chance += lowPowerBonus;
    
        return rand() % 100 < chance;
    }
};

}