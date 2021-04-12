#include "pepch.h"
#include "WindowsWindow.h"
#include "PEngine/Log.h"

#include "PEngine/Events/ApplicationEvent.h"
#include "PEngine/Events/KeyEvent.h"
#include "PEngine/Events/MouseEvent.h"

#include <glad/glad.h>

namespace PE
{
	static bool s_GLFWInitialized = false;

	/* Error Callback */
	static void GLFWErrorCallback(int a_error, const char* a_description)
	{
		PE_CORE_ERROR("GLFW Error ({0}): {1}", a_error, a_description);
	}

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
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		/* Creates the GLFW Window */
		m_window = glfwCreateWindow((int)a_props.m_width, (int)a_props.m_height, m_data.m_title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		int m_status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PE_CORE_ASSERT(m_status, "Failed to initialize GLAD");
		glfwSetWindowUserPointer(m_window, &m_data);
		SetVSync(true);

		#pragma region Callback Functions
		/* Set GLFW Callbacks */
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
		{
			/* Returns a void pointer to the Data struct of our Window */
			WindowData& m_data = *(WindowData*)glfwGetWindowUserPointer(window);
			m_data.m_width = width;
			m_data.m_height = height;

			WindowResizeEvent event(width, height);
			m_data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
		{
			/* Returns a void pointer to the Data struct of our Window */
			WindowData& m_data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			m_data.EventCallback(event);
		});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			/* Returns a void pointer to the Data struct of our Window */
			WindowData& m_data = *(WindowData*)glfwGetWindowUserPointer(window);
			/* Converts Keypressed Events into PE Key Events */
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					m_data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					m_data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					m_data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
		{
			/* Returns a void pointer to the Data struct of our Window */
			WindowData& m_data = *(WindowData*)glfwGetWindowUserPointer(window);
		
			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					m_data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					m_data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffSet, double yOffSet)
		{
			/* Returns a void pointer to the Data struct of our Window */
			WindowData& m_data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xOffSet, (float)yOffSet);
			m_data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
		{
			/* Returns a void pointer to the Data struct of our Window */
			WindowData& m_data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			m_data.EventCallback(event);
		});
		#pragma endregion
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_window);
	}
}