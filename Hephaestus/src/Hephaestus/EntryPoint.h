#pragma once
#include "Application.h"

#ifdef HEP_PLATFORM_WINDOWS

extern Hep::Application* Hep::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Hep::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif
