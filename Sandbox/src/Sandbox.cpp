#include <PEngine.h>

class ExampleLayer : public PE::Layer
{
public:

	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		PE_INFO("ExampleLayer::Update");
	}

	void OnEvent(PE::Event& a_event) override
	{
		PE_TRACE("{0}", a_event);
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