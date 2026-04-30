#include "Axiom/Scene/Scene.hpp"

namespace Axiom {

    void Scene::onUpdate(float dt)
    {
        camera.updateMatrix();
    }

    void Scene::onRender()
    {

    }
}