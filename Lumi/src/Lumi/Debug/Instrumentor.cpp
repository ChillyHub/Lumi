#include "pch.h"

#include "Instrumentor.h"

namespace Lumi
{
	// class Instrumentor -----------------------------------------------------------------------
	// ------------------------------------------------------------------------------------------
	void Instrumentor::BeginSession(const std::string_view name, const std::string_view filepath)
	{
		std::lock_guard lock(m_Mutex);
		if (m_CurrentSession)
		{
			// If there is already a current session, then close it before beginning new one.
			// Subsequent profiling output meant for the original session will end up in the
			// newly opened session instead.  That's better than having badly formatted
			// profiling output.
			if (Log::GetCoreLogger()) // Edge case: BeginSession() might be before Log::Init()
			{
				LUMI_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.",
					name, m_CurrentSession->Name);
			}
			InternalEndSession();
		}
		m_OutputStream.open(filepath);

		if (!m_OutputStream.is_open())
		{
			int i = 0;
			for (auto c : filepath)
			{
				if (c == '/' || c == '\\')
				{
					char path[1024];
					filepath.copy(path, i);
					path[i] = '\0';
					if (_access(path, 6) == -1)
					{
						int r = _mkdir(path);
					}
				}
				i++;
			}
			m_OutputStream.open(filepath);
		}

		if (m_OutputStream.is_open())
		{
			m_CurrentSession = new InstrumentationSession({ name });
			WriteHeader();
		}
		else
		{
			if (Log::GetCoreLogger()) // Edge case: BeginSession() might be before Log::Init()
			{
				LUMI_CORE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
			}
		}
	}

	void Instrumentor::EndSession()
	{
		std::lock_guard lock(m_Mutex);
		InternalEndSession();
	}

	void Instrumentor::WriteProfile(const ProfileResult& result)
	{
		std::stringstream json;

		json << std::setprecision(3) << std::fixed;
		json << ",\n\t\t{\n";
		json << "\t\t\t\"cat\": \"function\",\n";
		json << "\t\t\t\"dur\": " << (result.ElapsedTime.count()) << ",\n";
		json << "\t\t\t\"name\": \"" << result.Name << "\",\n";
		json << "\t\t\t\"ph\": \"X\",\n";
		json << "\t\t\t\"pid\": 0,\n";
		json << "\t\t\t\"tid\": " << result.ThreadID << ",\n";
		json << "\t\t\t\"ts\": " << result.Start.count() << "\n";
		json << "\t\t}";

		std::lock_guard lock(m_Mutex);
		if (m_CurrentSession)
		{
			m_OutputStream << json.str();
			m_OutputStream.flush();
		}
	}

	Instrumentor& Instrumentor::Get()
	{
		static Instrumentor instance;
		return instance;
	}

	Instrumentor::Instrumentor() 
		: m_CurrentSession(nullptr)
	{

	}

	Instrumentor::~Instrumentor()
	{
		EndSession();
	}

	void Instrumentor::WriteHeader()
	{
		m_OutputStream << "{\n\t\"otherData\": {},\n\t\"traceEvents\": [\n\t\t{}";
		m_OutputStream.flush();
	}

	void Instrumentor::WriteFooter()
	{
		m_OutputStream << "\n\t]\n}";
		m_OutputStream.flush();
	}

	void Instrumentor::InternalEndSession()
	{
		if (m_CurrentSession)
		{
			WriteFooter();
			m_OutputStream.close();
			delete m_CurrentSession;
			m_CurrentSession = nullptr;
		}
	}


	// class InstrumentationTimer ---------------------------------------------------------------
	// ------------------------------------------------------------------------------------------
	InstrumentationTimer::InstrumentationTimer(std::string_view name)
		: m_Name(name), m_Stopped(false)
	{
		m_StartTimePoint = std::chrono::steady_clock::now();
	}

	InstrumentationTimer::~InstrumentationTimer()
	{
		if (!m_Stopped)
			Stop();
	}

	void InstrumentationTimer::Stop()
	{
		auto endTimePoint = std::chrono::steady_clock::now();
		auto highResStart = FloatingPointMicroseconds(m_StartTimePoint.time_since_epoch());
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint)
			.time_since_epoch();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint)
			.time_since_epoch();
		auto elapsedTime = end - start;

		Instrumentor::Get().WriteProfile({ m_Name, highResStart, elapsedTime, std::this_thread::get_id() });

		m_Stopped = true;
	}
}