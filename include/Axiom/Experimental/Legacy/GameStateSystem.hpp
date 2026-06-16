#pragma once

enum class GameState
{
    Office,
    Camera,
    GameOver
};

class GameStateSystem
{
public:
    GameState state = GameState::Office;

    void toggleCamera()
    {
        if (state == GameState::Office)
            state = GameState::Camera;
        else if (state == GameState::Camera)
            state = GameState::Office;
    }

};