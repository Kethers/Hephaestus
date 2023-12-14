#include "heppch.h"
#include "RenderPass.h"

#include "Renderer.h"

#include "Hephaestus/Platform/OpenGL/OpenGLRenderPass.h"

namespace Hep
{
	Ref<RenderPass> RenderPass::Create(const RenderPassSpecification& spec)
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None: HEP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			case RendererAPIType::OpenGL: return Ref<OpenGLRenderPass>::Create(spec);
		}

		HEP_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
