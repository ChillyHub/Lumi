#include "pch.h"
#include "Log.h"

namespace Lumi
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		LM_PROFILE_FUNCTION();
		
		s_CoreLogger = spdlog::stdout_color_mt("Lumi");
		s_CoreLogger->set_level(spdlog::level::trace);
		s_ClientLogger = spdlog::stdout_color_mt("Client");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}