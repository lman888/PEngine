#include "pepch.h"

#include "App.h"
#include "PEngine/Log.h"
#include "PEngine/Input.h"

#include <glad/glad.h>

namespace PE
{

#define BIND_EVENT_FN(x) std::bind(&App::x, this, std::placeholders::_1)

	App* App::s_instance = nullptr;

	App::App()
	{
		PE_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		m_window = std::unique_ptr<Window>(Window::Create());
		/* EventCallback (used for events that happens to our window such as closing, resizing etc..) */
		m_window->SetEventCallback(BIND_EVENT_FN(OnEvent));


		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	void App::Run()
	{
		while (m_running)
		{
			glClearColor(1, 1, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			

			for (Layer* layer : m_layerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_layerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_window->OnUpdate();
		}
	}

	/* EventCallback will call this function */
	void App::OnEvent(Event& a_event)
	{
		EventDispatcher m_dispatcher(a_event);
		/* Informed the Dispatcher to check if the WindowCloseEvent is occuring */
		m_dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		/* Prints what Event is currently occuring*/
		//PE_CORE_TRACE("{0}", a_event);

		for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
		{
			(*--it)->OnEvent(a_event);
			if (a_event.m_handled)
			{
				break;
			}
		}
	}

	void App::PushLayer(Layer* a_layer)
	{
		m_layerStack.PushLayer(a_layer);
		a_layer->OnAttach();
	}

	void App::PushOverlay(Layer* a_layer)
	{
		m_layerStack.PushOverlay(a_layer);
		a_layer->OnAttach();
	}

	bool App::OnWindowClose(WindowCloseEvent& a_e)
	{
		m_running = false;
		return true;
	}
}