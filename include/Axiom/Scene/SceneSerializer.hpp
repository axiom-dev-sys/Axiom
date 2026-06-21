#pragma once

#include <string>

namespace Axiom {

    class Scene;

    class SceneSerializer
    {
    public:
        static void save(
            Scene& scene,
            const std::string& path
        );
    };

}