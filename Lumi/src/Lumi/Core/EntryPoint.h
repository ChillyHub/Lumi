#pragma once

#ifdef _LM_WINDOWS_

extern Lumi::Application* Lumi::CreateApplication();

int main(int argc, char* argv[])
{
	Lumi::Log::Init();

	LM_PROFILE_BEGIN_SESSION("Startup", "profile/Lumi_Startup_Profile.json");
	auto app = Lumi::CreateApplication();
	LM_PROFILE_END_SESSION();

	LM_PROFILE_BEGIN_SESSION("Running", "profile/Lumi_Running_Profile.json");
	app->Run();
	LM_PROFILE_END_SESSION();

	LM_PROFILE_BEGIN_SESSION("Shutdown", "profile/Lumi_Shutdown_Profile.json");
	delete app;
	LM_PROFILE_END_SESSION();
}

#endif // _LM_WINDOWS_
