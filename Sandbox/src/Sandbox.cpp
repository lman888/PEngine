#include <PEngine.h>

class Sandbox : public PE::App
{
public:
	Sandbox()
	{

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