#include <Hephaestus.h>
#include <Hephaestus/EntryPoint.h>

#include "EditorLayer.h"

class PoseidonApplication : public Hep::Application
{
public:
	PoseidonApplication(const Hep::ApplicationProps& props)
		: Application(props)
	{ }

	void OnInit() override
	{
		PushLayer(new Hep::EditorLayer());
	}
};

Hep::Application* Hep::CreateApplication()
{
	return new PoseidonApplication({ "Poseidon", 1600, 900 });
}
