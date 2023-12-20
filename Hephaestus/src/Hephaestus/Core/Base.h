#pragma once

#include <memory>
#include "Ref.h"

namespace Hep
{
	void InitializeCore();
	void ShutdownCore();
}

#ifndef HEP_PLATFORM_WINDOWS
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


#define HEP_EXPAND_VARGS(x) x
#include "Assert.h"

#define BIT(x) (1 << x)

#define HEP_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

// Pointer wrappers
namespace Hep
{
	template <typename T>
	using Scope = std::unique_ptr<T>;

	template <typename T, typename... Args>
	constexpr Scope<T> CreateScope(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	using byte = uint8_t;
}
