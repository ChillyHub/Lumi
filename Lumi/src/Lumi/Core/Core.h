#pragma once

#include "Platform/PlatformSystem.h"

#ifdef LM_PLATFORM_WINDOWS
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
	#if defined(LM_PLATFORM_WINDOWS)
		#define LM_DEBUGBREAK() __debugbreak()
	#elif defined(LM_PLATFORM_LINUX)
		#include <signal.h>
		#define LM_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define LM_ENABLE_ASSERTS
#else
	#define LM_DEBUGBREAK()
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

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
#define BIND_EVENT_DYNAMIC_FN(x, ins) std::bind(&x, ins, std::placeholders::_1)

#include "pch.h"

namespace Lumi
{
	template <typename T>
	using Scope = std::unique_ptr<T>;

	template <typename T>
	using Refer = std::shared_ptr<T>;
}