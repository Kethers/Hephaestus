#include "heppch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Hephaestus/Platform/OpenGL/OpenGLVertexArray.h"

namespace Hep
{
	VertexArray* VertexArray::Create()
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None:
			{
				HEP_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
				return nullptr;
			}
			case RendererAPIType::OpenGL: return new OpenGLVertexArray();
		}

		HEP_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}
