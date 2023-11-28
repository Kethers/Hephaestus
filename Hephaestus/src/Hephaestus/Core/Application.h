#pragma once

#include "Hephaestus/Core/Base.h"
#include "Hephaestus/Core/Window.h"
#include "Hephaestus/Core/LayerStack.h"

#include "Hephaestus/Core/Events/ApplicationEvent.h"

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

		std::string OpenFile(const std::string& filter) const;

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true, m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;
	};

	// Implemented by CLIENT
	Application* CreateApplication();
}
