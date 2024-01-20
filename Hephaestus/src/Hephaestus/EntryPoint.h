#pragma once

#ifdef HEP_PLATFORM_WINDOWS

extern Hep::Application* Hep::CreateApplication(int argc, char** argv);
inline bool g_ApplicationRunning = true;

int main(int argc, char** argv)
{
	while (g_ApplicationRunning)
	{
		Hep::InitializeCore();
		Hep::Application* app = Hep::CreateApplication(argc, argv);
		HEP_CORE_ASSERT(app, "Client Application is null!");
		app->Run();
		delete app;
		Hep::ShutdownCore();
	}
}

#endif
