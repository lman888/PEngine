#include "pepch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "GLFW/glfw3.h"

#include "PEngine/App.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace PE
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& m_io = ImGui::GetIO();
		m_io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		m_io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		/* TEMP: will has PEngine Key Codes */
		m_io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		m_io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		m_io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		m_io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		m_io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		m_io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		m_io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		m_io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		m_io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		m_io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		m_io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		m_io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		m_io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		m_io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		m_io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		m_io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
		m_io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		m_io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		m_io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		m_io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		m_io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		m_io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& m_io = ImGui::GetIO();
		App& m_app = App::Get();
		m_io.DisplaySize = ImVec2(m_app.GetWindow().GetWidth(), m_app.GetWindow().GetHeight());

		float m_time = (float)glfwGetTime();
		m_io.DeltaTime = m_Time > 0.0f ? (m_time - m_Time) : (1.0f / 60.0f);
		m_Time = m_time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool m_show = true;
		ImGui::ShowDemoWindow(&m_show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& a_event)
	{
		EventDispatcher m_dispatcher(a_event);
		m_dispatcher.Dispatch<MouseButtonPressedEvent>(PE_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		m_dispatcher.Dispatch<MouseButtonReleasedEvent>(PE_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		m_dispatcher.Dispatch<MouseMovedEvent>(PE_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		m_dispatcher.Dispatch<MouseScrolledEvent>(PE_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		m_dispatcher.Dispatch<KeyPressedEvent>(PE_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		m_dispatcher.Dispatch<KeyTypedEvent>(PE_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		m_dispatcher.Dispatch<KeyReleasedEvent>(PE_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		m_dispatcher.Dispatch<WindowResizeEvent>(PE_BIND_EVENT_FN(ImGuiLayer::OnWindowResizedEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& a_event)
	{
		ImGuiIO& m_io = ImGui::GetIO();
		m_io.MouseDown[a_event.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& a_event)
	{
		ImGuiIO& m_io = ImGui::GetIO();
		m_io.MouseDown[a_event.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& a_event)
	{
		ImGuiIO& m_io = ImGui::GetIO();
		m_io.MousePos = ImVec2(a_event.GetX(), a_event.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& a_event)
	{
		ImGuiIO& m_io = ImGui::GetIO();
		m_io.MouseWheelH += a_event.GetXOffSet();
		m_io.MouseWheel += a_event.GetYOffSet();

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& a_event)
	{
		ImGuiIO& m_io = ImGui::GetIO();
		m_io.KeysDown[a_event.GetKeyCode()] = true;

		/* If a key is pressed, we check to see if a Modifier is pressed */
		m_io.KeyCtrl = m_io.KeysDown[GLFW_KEY_LEFT_CONTROL] || m_io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		m_io.KeyShift = m_io.KeysDown[GLFW_KEY_LEFT_SHIFT] || m_io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		m_io.KeyAlt = m_io.KeysDown[GLFW_KEY_LEFT_ALT] || m_io.KeysDown[GLFW_KEY_RIGHT_ALT];
		m_io.KeySuper = m_io.KeysDown[GLFW_KEY_LEFT_SUPER] || m_io.KeysDown[GLFW_KEY_RIGHT_SUPER];


		m_io.SetClipboardTextFn = SetClipboardText;
		m_io.GetClipboardTextFn = GetClipboardText;

		App& m_app = App::Get();
		m_io.ClipboardUserData = m_app.GetWindow().GetNativeWindow();

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& a_event)
	{
		ImGuiIO& m_io = ImGui::GetIO();
		m_io.KeysDown[a_event.GetKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& a_event)
	{
		ImGuiIO& m_io = ImGui::GetIO();
		int keycode = a_event.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000)
			m_io.AddInputCharacter((unsigned short)keycode);

		return false;
	}

	bool ImGuiLayer::OnWindowResizedEvent(WindowResizeEvent& a_event)
	{
		ImGuiIO& m_io = ImGui::GetIO();
		m_io.DisplaySize = ImVec2(a_event.GetWidth(), a_event.GetHeight());
		m_io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, a_event.GetWidth(), a_event.GetHeight());

		return false;
	}

	void ImGuiLayer::SetClipboardText(void* a_data, const char* a_text)
	{
		glfwSetClipboardString((GLFWwindow*)a_data, a_text);
	}

	const char* ImGuiLayer::GetClipboardText(void* a_data)
	{
		return glfwGetClipboardString((GLFWwindow*)a_data);
	}
}