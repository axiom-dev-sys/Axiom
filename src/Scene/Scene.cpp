#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/RenderComponent.hpp"
#include "Axiom/Renderer/Texture.hpp"
#include "Axiom/Renderer/Renderer.hpp"
#include "Axiom/Core/Log.hpp"

namespace Axiom {

    void Scene::onUpdate(float dt)
    {

    }

    void Scene::onRender()
    {
        camera.updateMatrix();

        forEach([&](Entity* e)
            {
                auto rc = e->getComponent<RenderComponent>();
                if (!rc) return;

                    Texture* tex = rc->getTexture();
                if (!tex) return;

                Transform* tr = rc->getTransform();
                if (!tr) return;

                Axiom::Renderer::draw(*tex,
                    { tr->x, tr->y },
                    camera.getMatrix());
            });
    }
}