#include "heppch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hep
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				HEP_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}

		HEP_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}
