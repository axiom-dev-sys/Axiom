#pragma once
#include "Axiom/Scene/Component.hpp"
#include <unordered_map>
#include <typeindex>
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

    auto component = std::make_unique<T>(std::forward<Args>(args)...);

    T* ptr = component.get();

    m_Components[typeid(T)] = std::move(component);

    return ptr;
}

        template<typename T>
        T* getComponent() 
        {
            auto it = m_Components.find(typeid(T));
            if (it != m_Components.end())
                return dynamic_cast<T*>(it->second.get());

            return nullptr;
        }

        const std::string& getName() const
        {
            return m_Name;
        }

        void onUpdate()
        {
            for (auto& [type, component] : m_Components)
                component->onUpdate();
        }

    private:

        std::string m_Name;
        std::unordered_map<std::type_index, std::unique_ptr<Component>> m_Components;
    };

}