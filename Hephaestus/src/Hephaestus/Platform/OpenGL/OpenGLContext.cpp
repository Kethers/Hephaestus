#include "heppch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Hep
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		HEP_CORE_ASSERT(windowHandle, "WindowHandle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		glfwMaximizeWindow(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HEP_CORE_ASSERT(status, "Failed to initialized Glad!")

		// HEP_CORE_INFO("OpenGL Info:");
		// HEP_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		// HEP_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		// HEP_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
