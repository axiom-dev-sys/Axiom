#pragma once

#include <unordered_set>
#include <cstdint>

namespace Axiom {

    class Scene;
    class Entity;

    class CollisionSystem
    {
    public:
        void update(Scene& scene);

    private:
        std::unordered_set<std::uint64_t> m_PreviousCollisions;
        std::unordered_set<std::uint64_t> m_PreviousTriggers;

        std::uint64_t makeCollisionKey(Entity* a, Entity* b) const;

        void onCollisionEnter(Entity* a, Entity* b);
        void onCollisionStay(Entity* a, Entity* b);
        void onCollisionExit();

        void onTriggerEnter(Entity* a, Entity* b);
        void onTriggerStay(Entity* a, Entity* b);
        void onTriggerExit();
    };

}