#pragma once

#ifdef _LM_WINDOWS_
	#ifdef DLL_BUILD
		#ifdef LM_DLL_EXPORTS
			#define LUMI_API __declspec(dllexport)
		#else
			#define LUMI_API __declspec(dllimport)
		#endif
	#else
		#define LUMI_API
	#endif
#else
	#error Lumi only support Windows
#endif

#ifdef LUMI_DEBUG
	#define LM_ENABLE_ASSERTS
#endif // LUMI_DEBUG

#ifdef LM_ENABLE_ASSERTS
	#define LUMI_CLIENT_ASSERT(x, ...) { if(!(x)) \
		{ LUMI_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define LUMI_CORE_ASSERT(x, ...) { if(!(x)) \
		{ LUMI_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define LUMI_CLIENT_ASSERT(x, ...)
	#define LUMI_CORE_ASSERT(x, ...)
#endif // LM_ENABLE_ASSERTS


#define BIT(x) (1 << x)

// #include "pch.h"