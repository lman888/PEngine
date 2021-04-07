#pragma once

#include "Core.h"
#include "PEngine/Events/Event.h"
#include "Window.h"

namespace PE
{
	class PE_API App
	{
	public:
		App();

		void Run();

	private:
		std::unique_ptr<Window> m_window;
		bool m_running;
	};

	/* To be defined in Client */
	App* CreateApp();
}