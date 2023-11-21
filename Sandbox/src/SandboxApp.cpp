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
		if (Hep::Input::IsKeyPressed(HEP_KEY_TAB))
			HEP_TRACE("Tab Key is pressed (pool)!");
	}

	void OnEvent(Hep::Event& event) override
	{
		if (event.GetEventType() == Hep::EventType::KeyPressed)
		{
			auto e = static_cast<Hep::KeyPressedEvent&>(event);
			if (Hep::Input::IsKeyPressed(HEP_KEY_TAB))
				HEP_TRACE("Tab Key is pressed (event)!");
			HEP_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Hep::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};

Hep::Application* Hep::CreateApplication()
{
	return new Sandbox{};
}
