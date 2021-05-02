#pragma once

#ifdef PE_PLATFORM_WINDOWS
	#ifdef PE_BUILD_DLL
		#define PE_API __declspec(dllexport)
	#else
		#define PE_API __declspec(dllimport)
	#endif // PE_BUILD_DLL
#else
	#error PandaEngine only supports Windows!
#endif // PE_PLATFORM_WINDOWS

/* Checks a condition and logs a message if it fails (Like setting a breakpoint) */
#ifdef PE_ENABLE_ASSERTS
	#define PE_ASSERT(x, ...) {if(!(x)) {PE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define PE_CIRE_ASSERT(x, ...) {if(!(x)) {PE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define PE_ASSERT(x, ...)
	#define PE_CORE_ASSERT(x, ...)
#endif // PE_ENABLE_ASSERTS


/* Bit Field */
#define BIT(x) (1<<x)

#define PE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)