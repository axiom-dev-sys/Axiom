#pragma warning(disable : 26812)

#include "Axiom/Core/Engine.hpp"
#include "Axiom/Renderer/Renderer.hpp"
#include "Axiom/Renderer/Shader.hpp"
#include "Axiom/Resource/ResourceManager.hpp"
#include "Axiom/Experimental/Game/GameLayer.hpp"
#include "Axiom/Input/Input.hpp"
#include "Axiom/Core/Time.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace Axiom {

    Engine::Engine()
    {
        m_Window = new Window(1280, 720, "Axiom");

        Renderer::init();

        Input::setWindow(m_Window->getNative());

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        (void)io;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(m_Window->getNative(), true);
        ImGui_ImplOpenGL3_Init("#version 330");

        ResourceManager::init();

        m_Application.init();

        m_GameLayer = new GameLayer();
        m_LayerStack.pushLayer(m_GameLayer);
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

            for (Layer* layer : m_LayerStack)
                layer->onUpdate(dt);

            Renderer::clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            for (Layer* layer : m_LayerStack)
                layer->onRender();

            ImGui::Begin("Axiom Engine");

            ImGui::Text("Axiom Engine 0.4.4");

            ImGui::Separator();
            
            ImGui::Text(
                "State: %s",
                m_GameLayer->getGameState() == GameState::Pause
                ? "Pause"
                : "Gameplay"
            );

            ImGui::Text(
                "Scene: %s",
                m_GameLayer->getActiveSceneName().c_str());
            
            ImGui::Separator();

            ImGui::Text("FPS: %.1f", 1.0f / dt);

            ImGui::End();
            
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            m_Window->swapBuffers();
            m_Window->pollEvents();
        }

        glfwTerminate();
    }
}