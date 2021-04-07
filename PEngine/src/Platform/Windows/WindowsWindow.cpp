#include "pepch.h"
#include "WindowsWindow.h"
#include "PEngine/Log.h"

namespace PE
{
	static bool s_GLFWInitialized = false;
	Window* Window::Create(const WindowProps& a_props)
	{
		return new WindowsWindow(a_props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& a_props)
	{
		Init(a_props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void WindowsWindow::SetVSync(bool a_enabled)
	{
		if (a_enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.VSync = a_enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return false;
	}

	void WindowsWindow::Init(const WindowProps& a_props)
	{
		/* Sets up the Window Data based on our properties */
		m_data.m_title = a_props.m_title;
		m_data.m_width = a_props.m_width;
		m_data.m_height = a_props.m_height;

		PE_CORE_INFO("Creating Window {0} ({1}, {2})", a_props.m_height, a_props.m_width, a_props.m_height);

		/* Makes sure we only Initialize GLFW once */
		if (!s_GLFWInitialized)
		{
			int m_success = glfwInit();
			PE_CORE_ASSERT(m_success, "Could not initialize GLFW!");

			s_GLFWInitialized = true;
		}

		/* Creates the GLFW Window */
		m_window = glfwCreateWindow((int)a_props.m_width, (int)a_props.m_height, m_data.m_title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_window);
	}
}