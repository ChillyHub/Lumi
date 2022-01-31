#include <Lumi.h>

class Example : public Lumi::Application
{
public:
	Example();
	~Example();

private:

};

Example::Example()
{
}

Example::~Example()
{
}

Lumi::Application* Lumi::CreateApplication()
{
	return new Example();
}