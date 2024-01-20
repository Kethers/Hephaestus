#include "heppch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Hephaestus/Core/Log.h"

namespace Hep
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{}

	OpenGLContext::~OpenGLContext() = default;

	void OpenGLContext::Create()
	{
		HEP_CORE_INFO("OpenGLContext::Create");

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HEP_CORE_ASSERT(status, "Failed to initialize Glad!");

		HEP_CORE_INFO("OpenGL Info:");
		HEP_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		HEP_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		HEP_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));

#ifdef HEP_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		HEP_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Hephaestus requires at least OpenGL version 4.5!");
#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
