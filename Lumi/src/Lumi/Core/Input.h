#pragma once

#include "pch.h"
#include "Core.h"

namespace Lumi
{
	class LUMI_API Input
	{
	public:
		virtual ~Input() = default;

		static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

		static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		static std::pair<float, float> GetCursorPos() { return s_Instance->GetCursorPosImpl(); }
		static float GetCursorX() { return s_Instance->GetCursorXImpl(); }
		static float GetCursorY() { return s_Instance->GetCursorYImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetCursorPosImpl() = 0;
		virtual float GetCursorXImpl() = 0;
		virtual float GetCursorYImpl() = 0;
	private:
		static Input* s_Instance;
	};
}