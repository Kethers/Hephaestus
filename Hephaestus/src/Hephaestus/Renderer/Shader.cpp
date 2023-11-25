#include "heppch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hep
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				HEP_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		HEP_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}
