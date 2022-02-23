#pragma once

#include "Lumi/Core/Input.h"

namespace Lumi
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetCursorPosImpl() override;
		virtual float GetCursorXImpl() override;
		virtual float GetCursorYImpl() override;
	};
}
