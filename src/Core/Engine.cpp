#include "Axiom/Core/Engine.hpp"
#include "Axiom/Renderer/Renderer.hpp"
#include "Axiom/Resource/ResourceManager.hpp"
#include "Axiom/Experimental/Game/GameLayer.hpp"
#include "Axiom/Input/Input.hpp"
#include "Axiom/Core/Time.hpp"
#include "Axiom/Core/Paths.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <misc/freetype/imgui_freetype.h>

namespace Axiom {

    Engine::Engine()
    {
        m_Window = new Window(1280, 720, "Axiom");

        Renderer::init();

        Input::setWindow(m_Window->getNative());

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();

        io.Fonts->SetFontLoader(ImGuiFreeType::GetFontLoader());
        io.Fonts->FontLoaderFlags = ImGuiFreeTypeLoaderFlags_ForceAutoHint;

        io.Fonts->AddFontFromFileTTF(
            Paths::getAsset("fonts/Roboto-Medium.ttf").c_str(),
            18.0f,
            nullptr,
            io.Fonts->GetGlyphRangesCyrillic()
        );

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(m_Window->getNative(), true);
        ImGui_ImplOpenGL3_Init("#version 330");

        ResourceManager::init();

        m_Application.init();

        m_GameLayer = new GameLayer(&m_Application);
        m_Application.pushLayer(m_GameLayer);
    }

    Engine::~Engine()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        delete m_Window;
    }

    void Engine::run()
    {
        while (!m_Window->shouldClose())
        {
            Time::update();

            float dt = Time::getDeltaTime();

            m_Application.update(dt);

            if (m_GameLayer->isExitRequested())
            {
                m_Window->close();
            }

            Renderer::clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            m_Application.render();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            m_Window->swapBuffers();
            m_Window->pollEvents();
        }
    }
}