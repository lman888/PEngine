#include <PEngine.h>

#include "imgui/imgui.h"

class ExampleLayer : public PE::Layer
{
public:

	ExampleLayer()
		: Layer("Example")
	{
		
	}

	void OnUpdate() override
	{
		if (PE::Input::IsKeyPressed(PE_KEY_TAB))
			PE_TRACE("Tab key is pressed!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(PE::Event& a_event) override
	{
		if (a_event.GetEventType() == PE::EventType::KeyPressed)
		{
			PE::KeyPressedEvent& e = (PE::KeyPressedEvent&)a_event;
			PE_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};


class Sandbox : public PE::App
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

private:

};

PE::App* PE::CreateApp()
{
	return new Sandbox();
}