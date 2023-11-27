#include "heppch.h"
#include "Application.h"

#include "Hephaestus/Core/Log.h"

#include "Hephaestus/Renderer/Renderer.h"

#include "Input.h"

#include <GLFW/glfw3.h>

namespace Hep
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		HEP_CORE_ASSERT(!s_Instance, "Application already exist!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(HEP_BIND_EVENT_FN(Application::OnEvent));
		m_Window->SetVSync(false);

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::RenderImGui()
	{
		m_ImGuiLayer->Begin();
		for (Layer* layer : m_LayerStack)
			layer->OnImGuiRender();

		m_ImGuiLayer->End();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(HEP_BIND_EVENT_FN(Application::OnWindowClose));

		for (auto iter = m_LayerStack.end(); iter != m_LayerStack.begin();)
		{
			(*--iter)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		OnInit();
		while (m_Running)
		{
			auto time = static_cast<float>(glfwGetTime()); // Platform::GetTime
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			// Render ImGui on render thread
			Application* app = this;
			HEP_RENDER_1(app, { app->RenderImGui(); });

			Renderer::Get().WaitAndRender();

			m_Window->OnUpdate();
		}
		OnShutdown();
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		return false;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
