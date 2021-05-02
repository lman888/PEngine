#pragma once

#include "pepch.h"

#include "PEngine/Core.h"
#include "PEngine/Events/Event.h"

namespace PE
{
	struct WindowProps
	{
		std::string m_title;
		unsigned int m_width;
		unsigned int m_height;

		WindowProps(const std::string& a_title = "Panda Engine",
			unsigned int a_width = 1280,
			unsigned int a_height = 720)
			:m_title(a_title), m_width(a_width), m_height(a_height)
		{
		}
	};

	/* Interface representing a desktop system based Window */
	class PE_API Window
	{
	public:
		using EventCallBackfn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		/* Window Attributes */
		virtual void SetEventCallback(const EventCallBackfn& a_callBack) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		/* Returns our GLFW Window */
		virtual void* GetNativeWindow() const = 0;

		/* Implemented per platform */
		static Window* Create(const WindowProps& a_props = WindowProps());
	};

}