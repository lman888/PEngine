#pragma once

#ifdef PE_PLATFORM_WINDOWS

extern PE::App* PE::CreateApp();

int main(int argc, char** argv)
{
	PE::Log::Init();
	PE::Log::GetClientLogger()->warn("Initialized Client Log!");
	PE::Log::GetCoreLogger()->warn("Initialized Core Log!");

	auto app = PE::CreateApp();
	app->Run();
	delete app;
}

#endif