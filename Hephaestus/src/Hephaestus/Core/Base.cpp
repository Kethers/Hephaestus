#include "heppch.h"
#include "Base.h"

#include "Log.h"

#define HEP_BUILD_ID "v0.1a"

namespace Hep
{
	void InitializeCore()
	{
		Log::Init();

		HEP_CORE_TRACE("Hephaestus Engine {}", HEP_BUILD_ID);
		HEP_CORE_TRACE("Initializing...");
	}

	void ShutdownCore()
	{
		HEP_CORE_TRACE("Shutting down...");
	}
}
