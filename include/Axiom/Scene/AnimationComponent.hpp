#pragma once
#include "Axiom/Scene/Component.hpp"
#include "Axiom/Renderer/Texture.hpp"
#include "Axiom/Core/Time.hpp"


#include <vector>

namespace Axiom {

    class AnimationComponent : public Component
    {
    public:
        AnimationComponent(const std::vector<Texture*>& frames, float speed = 0.2f)
            : m_Frames(frames), m_Speed(speed) {
        }

        void onUpdate() override
        {
            m_Timer += Time::getDeltaTime();

            if (m_Timer >= m_Speed)
            {
                m_Timer = 0.0f;
                m_CurrentFrame++;

                if (m_CurrentFrame >= m_Frames.size())
                    m_CurrentFrame = 0;
            }
        }

        Texture* getCurrentFrame() const
        {
            if (m_Frames.empty()) return nullptr;
            return m_Frames[m_CurrentFrame];
        }

        void setFrames(const std::vector<Texture*>& frames)
        {
            m_Frames = frames;
            m_CurrentFrame = 0;
            m_Timer = 0.0f;
        }

    private:
        std::vector<Texture*> m_Frames;
        float m_Timer = 0.0f;
        float m_Speed;
        int m_CurrentFrame = 0;
        Axiom::AnimationComponent* animation = nullptr;
        std::vector<Axiom::Texture*> idleFrames;
        std::vector<Axiom::Texture*> runFrames;
    };

}