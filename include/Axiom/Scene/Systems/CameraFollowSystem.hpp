#pragma once

namespace Axiom {

    class Scene;
    class Entity;

class CameraFollowSystem
{
public:
    void follow(Scene& scene, Entity* target, float dt);
};

}