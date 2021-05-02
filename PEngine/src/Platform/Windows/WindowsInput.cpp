#include "pepch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>
#include "PEngine/App.h"

namespace PE
{
	Input* Input::s_instance = new WindowsInput();
	
	bool WindowsInput::IsKeyPressedImpl(int a_keyCode)
	{
		/* Gets the native GLFW Window */
		auto m_window = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
		/* Grabs what state a key is in when it is pressed */
		auto m_state = glfwGetKey(m_window, a_keyCode);
		/* Returns the state of the pressed key */
		return m_state == GLFW_PRESS || m_state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int a_button)
	{
		/* Gets the native GLFW Window */
		auto m_window = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
		/* Grabs what state a key is in when it is pressed */
		auto m_state = glfwGetMouseButton(m_window, a_button);

		return m_state == GLFW_PRESS;
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto[x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		/* Gets the native GLFW Window */
		auto m_window = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(m_window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}
}