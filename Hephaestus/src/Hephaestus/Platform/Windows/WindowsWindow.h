#pragma once

#include "Hephaestus/Core/Window.h"

#include <GLFW/glfw3.h>

namespace Hep
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void ProcessEvents() override;
		void SwapBuffers() override;

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }
		std::pair<uint32_t, uint32_t> GetSize() const override { return { m_Data.Width, m_Data.Height }; }

		std::pair<float, float> GetWindowPos() const override;

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		void Maximize() override;

		const std::string& GetTitle() const override { return m_Data.Title; }
		void SetTitle(const std::string& title) override;

		void* GetNativeWindow() const override { return m_Window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		Ref<RendererContext> GetRenderContext() override { return m_RendererContext; }

	private:
		GLFWwindow* m_Window;
		GLFWcursor* m_ImGuiMouseCursors[9] = { 0 };

		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
		float m_LastFrameTime = 0.0f;

		Ref<RendererContext> m_RendererContext;
	};
}
