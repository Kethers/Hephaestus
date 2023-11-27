#pragma once
#include "Core/Application.h"
#include "Core/Log.h"

#ifdef HEP_PLATFORM_WINDOWS

extern Hep::Application* Hep::CreateApplication();

int main(int argc, char** argv)
{
	Hep::Log::Init();
	HEP_CORE_WARN("Initialized Log!");
	int a = 5;
	HEP_INFO("Hello! Var={0}", a);

	auto app = Hep::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif
