#pragma once

#ifdef _LM_WINDOWS_
	#ifdef LM_DLL_EXPORTS
		#define LUMI_EXPORT __declspec(dllexport)
	#else
		#define LUMI_EXPORT __declspec(dllimport)
	#endif
#else
	#error Lumi only support Windows
#endif