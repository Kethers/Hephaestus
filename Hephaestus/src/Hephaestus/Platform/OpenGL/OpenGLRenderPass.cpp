#include "heppch.h"
#include "OpenGLRenderPass.h"

namespace Hep
{
	OpenGLRenderPass::OpenGLRenderPass(const RenderPassSpecification& spec)
		: m_Specification(spec)
	{ }

	OpenGLRenderPass::~OpenGLRenderPass() = default;
}
