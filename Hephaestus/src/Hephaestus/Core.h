#pragma once

#ifdef HEP_PLATFORM_WINDOWS
	#ifdef HEP_BUILD_DLL
		#define HEP_API __declspec(dllexport)
	#else
		#define HEP_API __declspec(dllimport)
	#endif
#else
	#error Hephaestus only supports Windows!
#endif
