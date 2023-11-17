#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Hep
{
	class HEP_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};


	Application* CreateApplication();
} // namespace Hep
