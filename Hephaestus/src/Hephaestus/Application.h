#pragma once

#include "Core.h"

#include "Window.h"
#include "Hephaestus/LayerStack.h"
#include "Hephaestus/Events/Event.h"
#include "Hephaestus/Events/ApplicationEvent.h"

namespace Hep
{
	class HEP_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		#pragma region static
		static Application* s_Instance;
		#pragma endregion static
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}