#pragma once

#include <memory>

namespace Hep
{
	void InitializeCore();
	void ShutdownCore();
}

#ifdef HEP_PLATFORM_WINDOWS
	#if HEP_DYNAMIC_LINK
		#ifdef HEP_BUILD_DLL
			#define HEP_API __declspec(dllexport)
		#else
			#define HEP_API __declspec(dllimport)
		#endif
	#else
		#define HEP_API
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

#ifdef _MSC_VER
	#define HEP_FORCE_INLINE __forceinline
#elif defined (__GNUC__ || __clang__)
	#defineHEP_FORCE_INLINE __attribute__((always_inline))
#else
	#define HEP_FORCE_INLINE inline
#endif

#ifdef HEP_DEBUG
	#define HEP_ENABLE_ASSERTS
#endif


#ifdef HEP_ENABLE_ASSERTS

	#define HEP_ASSERT_NO_MESSAGE(condition) { if(!(condition)) { HEP_ERROR("Assertion Failed!"); HEP_DEBUG_BREAK; } }
	#define HEP_ASSERT_MESSAGE(condition, ...) { if(!(condition)) { HEP_ERROR("Assertion Failed: {0}", __VA_ARGS__); HEP_DEBUG_BREAK; } }

	#define HEP_ASSERT_RESOLVE(arg1, arg2, macro, ...) macro

	#define HEP_ASSERT(...) HEP_ASSERT_RESOLVE(__VA_ARGS__, HEP_ASSERT_MESSAGE, HEP_ASSERT_NO_MESSAGE)(__VA_ARGS__)
	#define HEP_CORE_ASSERT(...) HEP_ASSERT_RESOLVE(__VA_ARGS__, HEP_ASSERT_MESSAGE, HEP_ASSERT_NO_MESSAGE)(__VA_ARGS__)
#else
	#define HEP_ASSERT(...)
	#define HEP_CORE_ASSERT(...)
#endif


#define BIT(x) (1 << x)

#define HEP_BIND_EVENT_FN(fn) std::bind(&##fn, this, std::placeholders::_1)

// Pointer wrappers
namespace Hep
{
	template <typename T>
	using Scope = std::unique_ptr<T>;

	template <typename T>
	using Ref = std::shared_ptr<T>;

	using byte = unsigned char;
}
