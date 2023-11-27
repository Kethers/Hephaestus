#pragma once

#include "Base.h"

#include "Window.h"
#include "LayerStack.h"
#include "Hephaestus/Core/Events/Event.h"
#include "Hephaestus/Core/Events/ApplicationEvent.h"

#include "Hephaestus/Core/Timestep.h"

#include "Hephaestus/ImGui/ImGuiLayer.h"

namespace Hep
{
	class HEP_API Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		virtual void OnInit() {}
		virtual void OnShutdown() {}
		virtual void OnUpdate() {}

		virtual void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void RenderImGui();

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		#pragma region static
		static Application* s_Instance;
		#pragma endregion static
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
