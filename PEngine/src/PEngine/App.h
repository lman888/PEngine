#pragma once

#include "Core.h"
#include "Window.h"
#include "PEngine/LayerStack.h"
#include "PEngine/Events/Event.h"
#include "PEngine/Events/ApplicationEvent.h"

namespace PE
{
	class PE_API App
	{
	public:
		App();

		void Run();

		void OnEvent(Event& a_event);

		void PushLayer(Layer* a_layer);
		void PushOverlay(Layer* a_layer);

		inline static App& Get(){return *s_instance; }
		inline Window& GetWindow() { return *m_window; }
	private:
		bool OnWindowClose(WindowCloseEvent& a_e);
		std::unique_ptr<Window> m_window;
		bool m_running;
		LayerStack m_layerStack;
	private:
		static App* s_instance;
	};

	/* To be defined in Client */
	App* CreateApp();
}