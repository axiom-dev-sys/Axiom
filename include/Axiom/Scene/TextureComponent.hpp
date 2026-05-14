#pragma once
#include "Component.hpp"
#include "Axiom/Renderer/Texture.hpp"

namespace Axiom {

    class TextureComponent : public Component
    {
    public:
        Texture* texture = nullptr;

        TextureComponent(Texture* tex)
            : texture(tex) {
        }
    };

}