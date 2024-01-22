#pragma once

#include "Hephaestus/Renderer/RendererContext.h"

struct GLFWwindow;

namespace Hep
{
	class OpenGLContext : public RendererContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		~OpenGLContext() override;

		void Create() override;
		void BeginFrame() override {}
		void SwapBuffers() override;
		void OnResize(uint32_t width, uint32_t height) override {}

	private:
		GLFWwindow* m_WindowHandle;
	};
}
