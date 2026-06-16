#pragma once

namespace Axiom {

    enum class EnemyState
    {
        Idle,
        Watching,
        Approaching,
        Attack
    };

    struct GameContext
    {
        float dt = 0.0f;

        float nightTime = 0.0f;
        float nightDuration = 60.0f;

        bool cameraOn = false;
        bool doorClosed = false;

        bool gameOver = false;
        bool win = false;

        float power = 100.0f;

        EnemyState enemyState = EnemyState::Idle;
    };

}