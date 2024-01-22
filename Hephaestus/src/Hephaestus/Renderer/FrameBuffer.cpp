#include "heppch.h"
#include "FrameBuffer.h"

#include "Hephaestus/Platform/OpenGL/OpenGLFrameBuffer.h"
#include "Hephaestus/Platform/Vulkan/VulkanFramebuffer.h"

#include "Hephaestus/Renderer/RendererAPI.h"

namespace Hep
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		Ref<Framebuffer> result = nullptr;

		switch (RendererAPI::Current())
		{
			case RendererAPIType::None: return nullptr;
			case RendererAPIType::OpenGL:
				result = Ref<OpenGLFramebuffer>::Create(spec);
				break;
			case RendererAPIType::Vulkan:
				result = Ref<VulkanFramebuffer>::Create(spec);
				break;
		}
		FramebufferPool::GetGlobal()->Add(result);
		return result;
	}

	FramebufferPool* FramebufferPool::s_Instance = new FramebufferPool;

	FramebufferPool::FramebufferPool(uint32_t maxFBs)
	{}

	std::weak_ptr<Framebuffer> FramebufferPool::AllocateBuffer()
	{
		// m_Pool.push_back();
		return std::weak_ptr<Framebuffer>();
	}

	void FramebufferPool::Add(const Ref<Framebuffer>& framebuffer)
	{
		m_Pool.push_back(framebuffer);
	}
}
