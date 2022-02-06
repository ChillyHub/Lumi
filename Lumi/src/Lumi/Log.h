#pragma once

#include "Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Lumi
{
	class LUMI_API Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define LUMI_CORE_ERROR(...) Lumi::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LUMI_CORE_WARN(...) Lumi::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LUMI_CORE_INFO(...) Lumi::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LUMI_CORE_TRACE(...) Lumi::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define LUMI_CLIENT_ERROR(...) Lumi::Log::GetClientLogger()->error(__VA_ARGS__)
#define LUMI_CLIENT_WARN(...) Lumi::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LUMI_CLIENT_INFO(...) Lumi::Log::GetClientLogger()->info(__VA_ARGS__)
#define LUMI_CLIENT_TRACE(...) Lumi::Log::GetClientLogger()->trace(__VA_ARGS__)