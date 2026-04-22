#pragma once
#include "Component.hpp"


#include <type_traits>
#include <memory>
#include <vector>
#include <string>
#include <utility>

namespace Axiom {

    class Entity
    {
    public:

        Entity(const std::string& name = "Entity")
            : m_Name(name) {}

        template<typename T, typename... Args>
        T* addComponent(Args&&... args)
        {
            static_assert(std::is_base_of<Component, T>::value, "T must be a Component");

            auto component = std::make_unique<T>(std::forward<Args>(args)...);

            T* rawPtr = component.get();

            m_Components.push_back(std::move(component));

            return rawPtr;
        }

        template<typename T>
        T* getComponent()
        {
            for (auto& component : m_Components)
            {
                if (T* cast = dynamic_cast<T*>(component.get()))
                    return cast;
            }

            return nullptr;
        }

        const std::string& getName() const
        {
            return m_Name;
        }

        void onUpdate()
        {
            for (auto& component : m_Components)
                component->onUpdate();
        }

    private:

        std::string m_Name;
        std::vector<std::unique_ptr<Component>> m_Components;
    };

}