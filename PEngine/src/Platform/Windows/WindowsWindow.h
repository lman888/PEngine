#pragma once

#include "PEngine/Window.h"
#include <GLFW/glfw3.h>

namespace PE
{
	class WindowsWindow : public Window
	{
	public: 
		WindowsWindow(const WindowProps& a_probs);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_data.m_width; }
		inline unsigned int GetHeight() const override { return m_data.m_height; }

		/* Window Attributes */
		inline void SetEventCallback(const EventCallBackfn& a_callback) { m_data.EventCallback = a_callback; }
		void SetVSync(bool a_enabled);
		bool IsVSync() const;

	private:

		virtual void Init(const WindowProps& a_props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_window;

		/* Stores all the acual data that is requested by GLFW */
		struct WindowData
		{
			std::string m_title;
			unsigned int m_width, m_height;
			bool VSync;

			EventCallBackfn EventCallback;
		};

		WindowData m_data;
	};
}