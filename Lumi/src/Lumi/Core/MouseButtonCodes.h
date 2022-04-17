#pragma once

//#define LUMI_MOUSE_BUTTON_1         0
//#define LUMI_MOUSE_BUTTON_2         1
//#define LUMI_MOUSE_BUTTON_3         2
//#define LUMI_MOUSE_BUTTON_4         3
//#define LUMI_MOUSE_BUTTON_5         4
//#define LUMI_MOUSE_BUTTON_6         5
//#define LUMI_MOUSE_BUTTON_7         6
//#define LUMI_MOUSE_BUTTON_8         7
//#define LUMI_MOUSE_BUTTON_LAST      LUMI_MOUSE_BUTTON_8
//#define LUMI_MOUSE_BUTTON_LEFT      LUMI_MOUSE_BUTTON_1
//#define LUMI_MOUSE_BUTTON_RIGHT     LUMI_MOUSE_BUTTON_2
//#define LUMI_MOUSE_BUTTON_MIDDLE    LUMI_MOUSE_BUTTON_3

namespace Lumi
{
	namespace Mouse
	{
		enum : uint16_t
		{
			B1         = 0,
			B2         = 1,
			B3         = 2,
			B4         = 3,
			B5         = 4,
			B6         = 5,
			B7         = 6,
			B8         = 7,
			Last       = B8,
			Left       = B1,
			Right      = B2,
			Middle     = B3
		};
	}
}