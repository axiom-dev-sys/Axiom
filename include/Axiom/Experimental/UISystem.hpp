#pragma once
#include <iostream>

namespace Axiom {

    class UISystem
    {
    public:
        void draw(float power)
        {
            std::cout << "Power: " << power << std::endl;
        }
    };
}