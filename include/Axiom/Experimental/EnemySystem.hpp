#pragma once

#include "Axiom/Experimental/Game/GameContext.hpp"

#include <cstdlib>

namespace Axiom {

class EnemySystem
{
public:
    void update(GameContext& ctx)
    {
        const bool watchingEnemy =
            ctx.cameraOn &&
            (
                (ctx.cameraView == CameraView::Camera1 &&
                    ctx.enemyState == EnemyState::Camera1)
                ||
                (ctx.cameraView == CameraView::Camera2 &&
                    ctx.enemyState == EnemyState::Camera2)
                );

        const float timerSpeed =
            watchingEnemy ? 0.5f : 1.0f;

        timer += ctx.dt * timerSpeed;

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
    float officeFarTime = 3.0f;
    float officeCloseTime = 2.0f;

    float camera2MinTime = 3.0f;
    float camera2MaxTime = 6.0f;

    float camera1MinTime = 3.0f;
    float camera1MaxTime = 6.0f;

    float stateDuration = 0.0f;

    float idleTime = 2.0f;
    float watchingTime = 3.0f;
    float approachTime = 2.0f;

    int aggression = 1;

    int cameraChance = 10;
    int normalChance = 40;
    int lowPowerBonus = 20;

    int stayChance = 15;
    int retreatChance = 20;

    void changeState(GameContext& ctx, EnemyState newState)
    {
        timer = 0.0f;
        ctx.enemyState = newState;

        applyDifficulty(ctx);

        switch (newState)
        {
        case EnemyState::Camera2:
            stateDuration = randomRange(
                camera2MinTime,
                camera2MaxTime
            );
            break;

        case EnemyState::Camera1:
            stateDuration = randomRange(
                camera1MinTime,
                camera1MaxTime
            );
            break;

        default:
            stateDuration = 0.0f;
            break;
        }
    }

    float randomRange(float minValue, float maxValue)
    {
        const float t =
            static_cast<float>(rand()) /
            static_cast<float>(RAND_MAX);

        return minValue + t * (maxValue - minValue);
    }

    bool shouldStay()
    {
        return rand() % 100 < stayChance;
    }

    bool shouldRetreat()
    {
        return rand() % 100 < retreatChance;
    }

    void applyDifficulty(const GameContext& ctx)
    {
        switch (ctx.difficulty)
        {
        case Difficulty::Easy:
            camera2MinTime = 5.0f;
            camera2MaxTime = 8.0f;

            camera1MinTime = 5.0f;
            camera1MaxTime = 8.0f;
            break;

        case Difficulty::Normal:
            camera2MinTime = 3.0f;
            camera2MaxTime = 6.0f;

            camera1MinTime = 3.0f;
            camera1MaxTime = 6.0f;
            break;

        case Difficulty::Hard:
            camera2MinTime = 2.0f;
            camera2MaxTime = 4.0f;

            camera1MinTime = 2.0f;
            camera1MaxTime = 4.0f;
            break;
        }
    }

    void updateHidden(GameContext& ctx)
    {
        if (timer > hiddenTime)
            changeState(ctx, EnemyState::Camera2);
    }

    void updateCamera2(GameContext& ctx)
    {
        if (timer <= stateDuration)
            return;

        if (shouldStay())
        {
            timer = 0.0f;

            stateDuration = randomRange(
                camera2MinTime,
                camera2MaxTime
            );
            return;
        }
        
        changeState(ctx, EnemyState::Camera1);
    }

    void updateCamera1(GameContext& ctx)
    {
        if (timer <= stateDuration)
            return;

        if (shouldRetreat())
        {
            changeState(ctx, EnemyState::Camera2);
            return;
        }

        if (shouldStay())
        {
            timer = 0.0f;

            stateDuration = randomRange(
                camera1MinTime,
                camera1MaxTime
            );
            return;
        }
        
        changeState(ctx, EnemyState::OfficeFar);
    }

    void updateOfficeFar(GameContext& ctx)
    {
        if (timer <= officeFarTime)
            return;
        
        if (shouldRetreat())
        {
            changeState(ctx, EnemyState::Camera1);
            return;
        }
        
        changeState(ctx, EnemyState::OfficeClose);
    }

    void updateOfficeClose(GameContext& ctx)
    {
        if (ctx.doorClosed)
        {
            changeState(ctx, EnemyState::Camera1);
            return;
        }

        if (timer <= officeCloseTime)
            return;

        if (shouldRetreat())
        {
            changeState(ctx, EnemyState::OfficeFar);
            return;
        }
        
        changeState(ctx, EnemyState::Attack);
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