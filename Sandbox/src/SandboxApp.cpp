#include <Hephaestus.h>

class Sandbox : public Hep::Application
{
public:
	Sandbox()
	{
		
	}

	~Sandbox()
	{
		
	}
};

Hep::Application* Hep::CreateApplication()
{
	return new Sandbox{};
}