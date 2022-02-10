#include <Lumi.h>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

class ExampleLayer : public Lumi::Layer
{
public:
	ExampleLayer() : Layer("Example") { }

	void OnUpdate() override
	{
		// LUMI_CLIENT_INFO("ExampleLayer::Update");
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Hello ImGui");
		ImGui::Text("Testing.");
		ImGui::End();
	}

	void OnEvent(Lumi::Event& event) override
	{
		// LUMI_CLIENT_TRACE("{0}", event);

		// if (event.GetEventType() == Lumi::EventType::KEY_PRESSED)
		// {
		// 	Lumi::KeyPressedEvent& e = (Lumi::KeyPressedEvent&)event;
		// 	if (Lumi::Input::IsKeyPressed(LUMI_KEY_TAB))
		// 		LUMI_CLIENT_INFO("Tab key is pressed!");
		// 	else
		// 		LUMI_CLIENT_TRACE("{0}", (char)e.GetKeyCode());
		// }
		// 
		// glm::mat4 model(1.0f);
		// model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		// glm::vec4 haha(1.0f, 2.0f, 3.0f, 1.0f);
		// haha = model * haha;
		// LUMI_CLIENT_INFO("{0}, {1}, {2}, {3}", haha.x, haha.y, haha.z, haha.w);
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
	// PushLayer(new Lumi::ImGuiLayer());
}

Example::~Example()
{
}

Lumi::Application* Lumi::CreateApplication()
{
	return new Example();
}