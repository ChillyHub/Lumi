#pragma once

#include "Component.h"
#include "Lumi/Scene/Entity.h"

namespace Lumi
{
	class Entity;

	class Script : public Component
	{
	public:
		bool Activated = true;
		Entity* entity;
	public:
		virtual void Start() {}
		virtual void Update(Timestep ts) {}

		virtual bool OnMouseButtonPressed(MouseButtonPressedEvent& e) { return false; }
		virtual bool OnMouseButtonRealeased(MouseButtonReleasedEvent& e) { return false; }
		virtual bool OnScrolleMouse(MouseScrolledEvent& e) { return false; }
		virtual bool OnMoveCursorPos(MouseMovedEvent& e) { return false; }
		virtual bool OnResizeWindow(WindowResizeEvent& e) { return false; }
	public:
		template <typename T>
		void Bind()
		{
			InitScript = [&]() { return static_cast<Script*>(new T(entity)); };
		}
		template <typename T>
		T& GetInstance()
		{
			return *(T*)instance;
		}
	public:
		Script(const Script& src) = default;
		Script(Entity* ent) : entity(ent) {}
	public:
		virtual void Init() final;
		virtual void OnEvent(Event& e) final;
		virtual void OnUpdate(Timestep ts) final;
		virtual void Disposed() final;

		operator bool() const { return instance; }
	private:
		Script* instance = nullptr;
		//Script* (*InitScript)() = nullptr;
		std::function<Script*()> InitScript = nullptr;
	};
}