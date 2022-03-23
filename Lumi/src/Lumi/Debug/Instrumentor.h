#pragma once

#include "pch.h"

#define LM_PROFILE 0

#if LM_PROFILE
	// Resolve which function signature macro will be used. Note that this only
	// is resolved when the (pre)compiler starts, so the syntax highlighting
	// could mark the wrong one in your editor!
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || \
		(defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define LM_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define LM_FUNC_SIG __PRETTY_FUNCTION__
	#elif (defined(__FUNCSIG__) || (_MSC_VER))
		#define LM_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define LM_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define LM_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define LM_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define LM_FUNC_SIG __func__
	#else
		#define HZ_FUNC_SIG "HZ_FUNC_SIG unknown!"
	#endif
	
	#define LM_PROFILE_BEGIN_SESSION(name, filepath) Lumi::Instrumentor::Get().BeginSession(name, filepath)
	#define LM_PROFILE_END_SESSION() Lumi::Instrumentor::Get().EndSession()
	#define LM_PROFILE_SCOPE_LINE2(name, line) constexpr auto fixedName##line = \
		Lumi::InstrumentorUtils::CleanupOutputString(name, "__cdecl ");\
		Lumi::InstrumentationTimer timer##line(fixedName##line.Data)
	#define LM_PROFILE_SCOPE_LINE(name, line) LM_PROFILE_SCOPE_LINE2(name, line)
	#define LM_PROFILE_SCOPE(name) LM_PROFILE_SCOPE_LINE(name, __LINE__)
	#define LM_PROFILE_FUNCTION() LM_PROFILE_SCOPE(LM_FUNC_SIG)
#else
	#define LM_PROFILE_BEGIN_SESSION(name, filepath)
	#define LM_PROFILE_END_SESSION()
	#define LM_PROFILE_SCOPE(name)
	#define LM_PROFILE_FUNCTION()
#endif

namespace Lumi
{
	using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;
	
	struct ProfileResult
	{
		std::string_view Name;

		FloatingPointMicroseconds Start;
		std::chrono::microseconds ElapsedTime;
		std::thread::id ThreadID;
	};

	struct InstrumentationSession
	{
		std::string_view Name;
	};

	class Instrumentor
	{
	public:
		Instrumentor(const Instrumentor&) = delete;
		Instrumentor(Instrumentor&&) = delete;

		void BeginSession(const std::string_view name, const std::string_view filepath = "result.json");
		void EndSession();
		void WriteProfile(const ProfileResult& result);
	public:
		static Instrumentor& Get();
	private:
		Instrumentor();
		~Instrumentor();

		void WriteHeader();
		void WriteFooter();

		// Note: you must already own lock on m_Mutex before
		// calling InternalEndSession()
		void InternalEndSession();
	private:
		std::mutex m_Mutex;
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;
	};

	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(std::string_view name);
		~InstrumentationTimer();

		void Stop();
	private:
		std::string_view m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimePoint;
		bool m_Stopped;
	};

	namespace InstrumentorUtils
	{

		template <size_t N>
		struct ChangeResult
		{
			char Data[N];
		};

		template <size_t N, size_t K>
		constexpr auto CleanupOutputString(const char(&expr)[N], const char(&remove)[K])
		{
			ChangeResult<N> result = {};

			size_t srcIndex = 0;
			size_t dstIndex = 0;
			while (srcIndex < N)
			{
				size_t matchIndex = 0;
				while (matchIndex < K - 1 && srcIndex + matchIndex < N - 1 &&
					expr[srcIndex + matchIndex] == remove[matchIndex])
				{
					matchIndex++;
				}
				if (matchIndex == K - 1)
				{
					srcIndex += matchIndex;
				}
				result.Data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];
				srcIndex++;
			}
			return result;
		}
	}
}