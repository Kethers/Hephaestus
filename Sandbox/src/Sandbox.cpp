#if 0
#include "Hephaestus.h"
#include "Hephaestus/EntryPoint.h"

#include "Hephaestus/Platform/Vulkan/VulkanTestLayer.h"

using namespace Hep;

class SandboxLayer : public Layer
{
public:
	SandboxLayer()
	{
	}

	virtual ~SandboxLayer()
	{
	}

	virtual void OnAttach() override
	{
		FramebufferSpecification framebufferSpec;
		framebufferSpec.ClearColor = { 0.0f, 0.8f, 0.0f, 1.0f };
		framebufferSpec.SwapChainTarget = true;

		RenderPassSpecification renderPassSpec;
		//renderPassSpec.TargetFramebuffer = Framebuffer::Create(framebufferSpec);

		//m_RenderPass = RenderPass::Create(renderPassSpec);
	}

	virtual void OnDetach() override
	{
	}

	virtual void OnUpdate(Timestep ts) override
	{
		//Renderer::BeginRenderPass(m_RenderPass);

		//Renderer::EndRenderPass();
	}

	virtual void OnImGuiRender() override
	{
	
	}

	virtual void OnEvent(Hep::Event& event) override
	{
	}
private:
	Ref<RenderPass> m_RenderPass;
};

class Sandbox : public Hep::Application
{
public:
	Sandbox()
	{
	}

	virtual void OnInit() override
	{
		//PushLayer(new SandboxLayer());
		PushLayer(new VulkanTestLayer());
	}
};

Hep::Application* Hep::CreateApplication()
{
	RendererAPI::SetAPI(RendererAPIType::Vulkan);
	return new Sandbox();
}
#endif