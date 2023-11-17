#include "Application.h"

#include "Hephaestus/Events/ApplicationEvent.h"
#include "Hephaestus/Log.h"

namespace Hep
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		HEP_TRACE(e);

		while (true)
		{
			
		}
	}
}
