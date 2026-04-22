#pragma once
#include <iostream>



class UISystem
{
public:
    void draw(float power)
    {
        std::cout << "Power: " << power << std::endl;
    }
};