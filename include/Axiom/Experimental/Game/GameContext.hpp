#pragma once

namespace Axiom {

    enum class EnemyState
    {
        Idle,
        Watching,
        Approaching,
        Attack,

        Hidden,
        Camera2,
        Camera1,
        OfficeFar,
        OfficeClose
    };

    enum class OfficeState
    {
        Normal,
        DoorClosed,
        EnemyFar,
        EnemyClose,
        PowerOut
    };

    enum class CameraView
    {
        None,
        Camera1,
        Camera2
    };

    enum class Difficulty
    {
        Easy,
        Normal,
        Hard
    };

    struct GameContext
    {
        int night = 1;

        float dt = 0.0f;

        float nightTime = 0.0f;
        float nightDuration = 75.0f;

        bool cameraOn = false;
        bool doorClosed = false;

        bool gameOver = false;
        bool win = false;

        float power = 100.0f;

        EnemyState enemyState = EnemyState::Hidden;

        Difficulty difficulty = Difficulty::Normal;

        CameraView cameraView = CameraView::Camera1;
    };

}