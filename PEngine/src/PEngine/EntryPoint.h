#pragma once

#ifdef PE_PLATFORM_WINDOWS

extern PE::App* PE::CreateApp();

int main(int argc, char** argv)
{
	auto app = PE::CreateApp();
	app->Run();
	delete app;
}

#endif