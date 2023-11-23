#pragma once

#include "Core.h"

#include "Window.h"
#include "Hephaestus/LayerStack.h"
#include "Hephaestus/Events/Event.h"
#include "Hephaestus/Events/ApplicationEvent.h"

#include "Hephaestus/ImGui/ImGuiLayer.h"

#include "Hephaestus/Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

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
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;
		#pragma region static
		static Application* s_Instance;
		#pragma endregion static
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
