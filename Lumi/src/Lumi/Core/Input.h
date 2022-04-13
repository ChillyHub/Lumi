#pragma once

#include "pch.h"
#include "Core.h"

namespace Lumi
{
	class LUMI_API Input
	{
	public:
		static bool IsKeyPressed(int keycode);

		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetCursorPos();
		static float GetCursorX();
		static float GetCursorY();
	};
}