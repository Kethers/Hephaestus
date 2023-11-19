#include <Hephaestus.h>

class ExampleLayer : public Hep::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		HEP_INFO("ExampleLayer::Update");
	}

	void OnEvent(Hep::Event& event) override
	{
		HEP_TRACE("{0}", event);
	}
};

class Sandbox : public Hep::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Hep::ImGuiLayer());
	}

	~Sandbox()
	{
	}
};

Hep::Application* Hep::CreateApplication()
{
	return new Sandbox{};
}
