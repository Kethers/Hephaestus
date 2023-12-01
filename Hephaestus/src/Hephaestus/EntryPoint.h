#pragma once

#ifdef HEP_PLATFORM_WINDOWS

extern Hep::Application* Hep::CreateApplication();

int main(int argc, char** argv)
{
	Hep::InitializeCore();
	Hep::Application* app = Hep::CreateApplication();
	HEP_CORE_ASSERT(app, "Client Application is null!");
	app->Run();
	delete app;
	Hep::ShutdownCore();
}

#endif
