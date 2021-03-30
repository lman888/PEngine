#include "pepch.h"

#include "App.h"

#include "PEngine/Events/ApplicationEvent.h"
#include "PEngine/Log.h"

namespace PE
{
	App::App()
	{
	}

	void App::Run()
	{
		WindowResizeEvent e(1280, 720);
		PE_TRACE(e);
		PE_WARN(e);

		while (true);
	}
}