#pragma once



namespace Axiom {

    class Time
    {
    public:
        static void update();

        static float getDeltaTime();

    private:
        static float s_DeltaTime;
        static float s_LastTime;
    };

}