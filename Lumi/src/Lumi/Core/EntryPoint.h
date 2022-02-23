#pragma once

#ifdef _LM_WINDOWS_

extern Lumi::Application* Lumi::CreateApplication();

int main(int argc, char* argv[])
{
	Lumi::Log::Init();
	LUMI_CORE_INFO("Lumi info.");
	LUMI_CLIENT_INFO("Client info.");

	auto app = Lumi::CreateApplication();
	app->Run();
	delete app;
}

#endif // _LM_WINDOWS_
