#include "pepch.h"

#include "App.h"

#include "PEngine/Events/ApplicationEvent.h"
#include "PEngine/Log.h"

#include "GLFW/glfw3.h"

namespace PE
{
	App::App()
	{
		m_window = std::unique_ptr<Window>(Window::Create());
	}

	void App::Run()
	{
		while (m_running)
		{
			glClearColor(1, 1, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->OnUpdate();
		}
	}
}