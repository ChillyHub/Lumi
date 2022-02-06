#include <Lumi.h>

class ExampleLayer : public Lumi::Layer
{
public:
	ExampleLayer() : Layer("Example") { }

	void OnUpdate() override
	{
		LUMI_CLIENT_INFO("ExampleLayer::Update");
	}

	void OnEvent(Lumi::Event& event) override
	{
		LUMI_CLIENT_TRACE("{0}", event);
	}
};

class Example : public Lumi::Application
{
public:
	Example();
	~Example();

private:

};

Example::Example()
{
	PushLayer(new ExampleLayer());
	PushLayer(new Lumi::ImGuiLayer());
}

Example::~Example()
{
}

Lumi::Application* Lumi::CreateApplication()
{
	return new Example();
}