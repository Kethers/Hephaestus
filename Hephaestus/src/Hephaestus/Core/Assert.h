#pragma once

#ifdef HEP_DEBUG
	#define HEP_ENABLE_ASSERTS
#endif

#ifdef HEP_ENABLE_ASSERTS
	#define HEP_ASSERT_NO_MESSAGE(condition) { if(!(condition)) { HEP_ERROR("Assertion Failed"); __debugbreak(); } }
	#define HEP_ASSERT_MESSAGE(condition, ...) { if(!(condition)) { HEP_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

	#define HEP_ASSERT_RESOLVE(arg1, arg2, macro, ...) macro
	#define HEP_GET_ASSERT_MACRO(...) HEP_EXPAND_VARGS(HEP_ASSERT_RESOLVE(__VA_ARGS__, HEP_ASSERT_MESSAGE, HEP_ASSERT_NO_MESSAGE))

	#define HEP_ASSERT(...) HEP_EXPAND_VARGS( HEP_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )
	#define HEP_CORE_ASSERT(...) HEP_EXPAND_VARGS( HEP_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )
#else
	#define HEP_ASSERT(...)
	#define HEP_CORE_ASSERT(...)
#endif
