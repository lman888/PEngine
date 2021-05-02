#pragma once

#include "PEngine/Layer.h"

#include "PEngine/Events/ApplicationEvent.h"
#include "PEngine/Events/KeyEvent.h"
#include "PEngine/Events/MouseEvent.h"

namespace PE
{
	class PE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& a_event);

	private:
	bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& a_event);
	bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& a_event);
	bool OnMouseMovedEvent(MouseMovedEvent& a_event);
	bool OnMouseScrolledEvent(MouseScrolledEvent& a_event);
	bool OnKeyPressedEvent(KeyPressedEvent& a_event);
	bool OnKeyReleasedEvent(KeyReleasedEvent& a_event);
	bool OnKeyTypedEvent(KeyTypedEvent& a_event);
	bool OnWindowResizedEvent(WindowResizeEvent& a_event);
	static void SetClipboardText(void* a_data, const char* a_text);
	static const char* GetClipboardText(void* a_data);

	private:
		float m_Time = 0.0f;
	};
}