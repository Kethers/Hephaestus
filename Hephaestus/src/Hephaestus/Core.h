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


#ifdef _MSC_VER
#define HEP_DEBUG_BREAK __debugbreak();
#elif defined (__GNUC__ || __clang__)
	#define HEP_DEBUG_BREAK __builtin_trap();
#else
	#define HEP_DEBUG_BREAK
#endif


#ifdef HEP_ENABLE_ASSERTS
	#define HEP_ASSERT(x, ...) { if (!(x)) { HEP_ERROR("Assertion Failed: {0}", __VA_ARGS__); HEP_DEBUG_BREAK; } }
	#define HEP_CORE_ASSERT(x, ...) { if (!(x)) { HEP_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); HEP_DEBUG_BREAK; } }
#else
#define HEP_ASSERT(x, ...)
#define HEP_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

#define HEP_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
