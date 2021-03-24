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

/* Bit Field */
#define BIT(x) (1<<x)