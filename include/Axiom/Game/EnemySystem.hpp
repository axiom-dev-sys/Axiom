#pragma once

#include "Axiom/Game/GameContext.hpp"

using namespace Axiom;

class EnemySystem
{
public:
    void update(GameContext& ctx)
    {
        timer += ctx.dt;

        switch (ctx.enemyState)
        {
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
        }
    }

private:
    float timer = 0.0f;

    void changeState(GameContext& ctx, EnemyState newState)
    {
        timer = 0.0f;
        ctx.enemyState = newState;
    }

    void updateIdle(GameContext& ctx)
    {
        if (timer > 2.0f && randomChance(ctx))
            changeState(ctx, EnemyState::Watching);
    }

    void updateWatching(GameContext& ctx)
    {
        if (!ctx.cameraOn && timer > 3.0f)
            changeState(ctx, EnemyState::Approaching);
    }

    void updateApproaching(GameContext& ctx)
    {
        if (ctx.cameraOn)
            changeState(ctx, EnemyState::Watching);

        if (timer > 2.0f)
            changeState(ctx, EnemyState::Attack);
    }

    void updateAttack(GameContext& ctx)
    {
        if (!ctx.doorClosed)
            ctx.gameOver = true;
        else
            changeState(ctx, EnemyState::Idle);
    }

    bool randomChance(GameContext& ctx)
    {
        int chance = ctx.cameraOn ? 10 : 40;

        if (ctx.power < 20)
            chance += 20;

        return rand() % 100 < chance;
    }
};