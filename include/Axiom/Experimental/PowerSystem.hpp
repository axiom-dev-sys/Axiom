#pragma once

#include "Axiom/Experimental/Game/GameContext.hpp"

namespace Axiom {

    class PowerSystem
    {
    public:
        void update(GameContext& ctx)
        {
            const float difficultyMultiplier =
                getDifficultyMultiplier(ctx.difficulty);

            float drain = baseDrain;

            if (ctx.cameraOn)
                drain += cameraDrain;

            if (ctx.doorClosed)
                drain += doorDrain;

            ctx.power -=
                drain *
                difficultyMultiplier *
                ctx.dt;
            
            if (ctx.power <= 0.0f)
            {
                ctx.power = 0.0f;
                ctx.gameOver = true;
            }
        }

        float getDifficultyMultiplier(
            Difficulty difficulty) const
        {
            switch (difficulty)
            {
            case Difficulty::Easy:
                return 0.75f;

            case Difficulty::Normal:
                return 1.0f;

            case Difficulty::Hard:
                return 1.25f;

            default:
                return 1.0f;
            }
        }

    private:
        float baseDrain = 0.5f;
        float cameraDrain = 4.0f;
        float doorDrain = 5.0f;
    };
}