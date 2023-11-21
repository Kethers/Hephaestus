#pragma once

#include "Hephaestus/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Hep
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}
