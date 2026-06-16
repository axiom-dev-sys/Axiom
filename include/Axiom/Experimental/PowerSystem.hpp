#pragma once

#include "Axiom/Experimental/Game/GameContext.hpp"

namespace Axiom {

    class PowerSystem
    {
    public:
        void update(GameContext& ctx)
        {
            ctx.power -= 1.0f * ctx.dt;

            if (ctx.cameraOn)
                ctx.power -= 10.0f * ctx.dt;

            if (ctx.doorClosed)
                ctx.power -= 5.0f * ctx.dt;
            
            if (ctx.power <= 0.0f)
            {
                ctx.power = 0.0f;
                ctx.gameOver = true;
            }
        }
    };
}