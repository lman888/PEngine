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

		PE_CORE_TRACE(e);
		PE_CORE_INFO(e);
		PE_CORE_WARN(e);
		PE_CORE_ERROR(e);
		PE_TRACE(e);
		PE_INFO(e);
		PE_WARN(e);
		PE_ERROR(e);

		while (true);
	}
}