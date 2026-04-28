#pragma once
#include "GameContext.hpp"

namespace Axiom {

    class PowerSystem
    {
    public:
        void update(GameContext& ctx)
        {
            if (ctx.cameraOn)
                ctx.power -= 10.0f * ctx.dt;

            if (ctx.doorClosed)
                ctx.power -= 5.0f * ctx.dt;

            if (ctx.power < 0)
                ctx.power = 0;

            if (ctx.power <= 0)
                ctx.gameOver = true;
        }
    };
}