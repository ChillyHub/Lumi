#pragma once

namespace Lumi
{
	/* The unknown key */
#define LUMI_KEY_UNKNOWN            -1

/* Printable keys */
//#define LUMI_KEY_SPACE              32
//#define LUMI_KEY_APOSTROPHE         39  /* ' */
//#define LUMI_KEY_COMMA              44  /* , */
//#define LUMI_KEY_MINUS              45  /* - */
//#define LUMI_KEY_PERIOD             46  /* . */
//#define LUMI_KEY_SLASH              47  /* / */
//#define LUMI_KEY_0                  48
//#define LUMI_KEY_1                  49
//#define LUMI_KEY_2                  50
//#define LUMI_KEY_3                  51
//#define LUMI_KEY_4                  52
//#define LUMI_KEY_5                  53
//#define LUMI_KEY_6                  54
//#define LUMI_KEY_7                  55
//#define LUMI_KEY_8                  56
//#define LUMI_KEY_9                  57
//#define LUMI_KEY_SEMICOLON          59  /* ; */
//#define LUMI_KEY_EQUAL              61  /* = */
//#define LUMI_KEY_A                  65
//#define LUMI_KEY_B                  66
//#define LUMI_KEY_C                  67
//#define LUMI_KEY_D                  68
//#define LUMI_KEY_E                  69
//#define LUMI_KEY_F                  70
//#define LUMI_KEY_G                  71
//#define LUMI_KEY_H                  72
//#define LUMI_KEY_I                  73
//#define LUMI_KEY_J                  74
//#define LUMI_KEY_K                  75
//#define LUMI_KEY_L                  76
//#define LUMI_KEY_M                  77
//#define LUMI_KEY_N                  78
//#define LUMI_KEY_O                  79
//#define LUMI_KEY_P                  80
//#define LUMI_KEY_Q                  81
//#define LUMI_KEY_R                  82
//#define LUMI_KEY_S                  83
//#define LUMI_KEY_T                  84
//#define LUMI_KEY_U                  85
//#define LUMI_KEY_V                  86
//#define LUMI_KEY_W                  87
//#define LUMI_KEY_X                  88
//#define LUMI_KEY_Y                  89
//#define LUMI_KEY_Z                  90
//#define LUMI_KEY_LEFT_BRACKET       91  /* [ */
//#define LUMI_KEY_BACKSLASH          92  /* \ */
//#define LUMI_KEY_RIGHT_BRACKET      93  /* ] */
//#define LUMI_KEY_GRAVE_ACCENT       96  /* ` */
//#define LUMI_KEY_WORLD_1            161 /* non-US #1 */
//#define LUMI_KEY_WORLD_2            162 /* non-US #2 */
//
///* Function keys */
//#define LUMI_KEY_ESCAPE             256
//#define LUMI_KEY_ENTER              257
//#define LUMI_KEY_TAB                258
//#define LUMI_KEY_BACKSPACE          259
//#define LUMI_KEY_INSERT             260
//#define LUMI_KEY_DELETE             261
//#define LUMI_KEY_RIGHT              262
//#define LUMI_KEY_LEFT               263
//#define LUMI_KEY_DOWN               264
//#define LUMI_KEY_UP                 265
//#define LUMI_KEY_PAGE_UP            266
//#define LUMI_KEY_PAGE_DOWN          267
//#define LUMI_KEY_HOME               268
//#define LUMI_KEY_END                269
//#define LUMI_KEY_CAPS_LOCK          280
//#define LUMI_KEY_SCROLL_LOCK        281
//#define LUMI_KEY_NUM_LOCK           282
//#define LUMI_KEY_PRINT_SCREEN       283
//#define LUMI_KEY_PAUSE              284
//#define LUMI_KEY_F1                 290
//#define LUMI_KEY_F2                 291
//#define LUMI_KEY_F3                 292
//#define LUMI_KEY_F4                 293
//#define LUMI_KEY_F5                 294
//#define LUMI_KEY_F6                 295
//#define LUMI_KEY_F7                 296
//#define LUMI_KEY_F8                 297
//#define LUMI_KEY_F9                 298
//#define LUMI_KEY_F10                299
//#define LUMI_KEY_F11                300
//#define LUMI_KEY_F12                301
//#define LUMI_KEY_F13                302
//#define LUMI_KEY_F14                303
//#define LUMI_KEY_F15                304
//#define LUMI_KEY_F16                305
//#define LUMI_KEY_F17                306
//#define LUMI_KEY_F18                307
//#define LUMI_KEY_F19                308
//#define LUMI_KEY_F20                309
//#define LUMI_KEY_F21                310
//#define LUMI_KEY_F22                311
//#define LUMI_KEY_F23                312
//#define LUMI_KEY_F24                313
//#define LUMI_KEY_F25                314
//#define LUMI_KEY_KP_0               320
//#define LUMI_KEY_KP_1               321
//#define LUMI_KEY_KP_2               322
//#define LUMI_KEY_KP_3               323
//#define LUMI_KEY_KP_4               324
//#define LUMI_KEY_KP_5               325
//#define LUMI_KEY_KP_6               326
//#define LUMI_KEY_KP_7               327
//#define LUMI_KEY_KP_8               328
//#define LUMI_KEY_KP_9               329
//#define LUMI_KEY_KP_DECIMAL         330
//#define LUMI_KEY_KP_DIVIDE          331
//#define LUMI_KEY_KP_MULTIPLY        332
//#define LUMI_KEY_KP_SUBTRACT        333
//#define LUMI_KEY_KP_ADD             334
//#define LUMI_KEY_KP_ENTER           335
//#define LUMI_KEY_KP_EQUAL           336
//#define LUMI_KEY_LEFT_SHIFT         340
//#define LUMI_KEY_LEFT_CONTROL       341
//#define LUMI_KEY_LEFT_ALT           342
//#define LUMI_KEY_LEFT_SUPER         343
//#define LUMI_KEY_WINDOWS            343
//#define LUMI_KEY_LEFT_COMMAND       343
//#define LUMI_KEY_RIGHT_SHIFT        344
//#define LUMI_KEY_RIGHT_CONTROL      345
//#define LUMI_KEY_RIGHT_ALT          346
//#define LUMI_KEY_RIGHT_SUPER        347
//#define LUMI_KEY_RIGHT_COMMAND      347
//#define LUMI_KEY_MENU               348
//
//#define LUMI_KEY_LAST               LUMI_KEY_MENU


/*! @brief If this bit is set one or more Shift keys were held down.
 *
 *  If this bit is set one or more Shift keys were held down.
 */
#define LUMI_MOD_SHIFT           0x0001
 /*! @brief If this bit is set one or more Control keys were held down.
 *
 *  If this bit is set one or more Control keys were held down.
 */
#define LUMI_MOD_CONTROL         0x0002
 /*! @brief If this bit is set one or more Alt keys were held down.
  *
  *  If this bit is set one or more Alt keys were held down.
  */
#define LUMI_MOD_ALT             0x0004
  /*! @brief If this bit is set one or more Super keys were held down.
  *
  *  If this bit is set one or more Super keys were held down.
  */
#define LUMI_MOD_SUPER           0x0008
  /*! @brief If this bit is set the Caps Lock key is enabled.
  *
  *  If this bit is set the Caps Lock key is enabled and the @ref
  *  GLFW_LOCK_KEY_MODS input mode is set.
  */
#define LUMI_MOD_CAPS_LOCK       0x0010
  /*! @brief If this bit is set the Num Lock key is enabled.
   *
   *  If this bit is set the Num Lock key is enabled and the @ref
   *  GLFW_LOCK_KEY_MODS input mode is set.
   */
#define LUMI_MOD_NUM_LOCK        0x0020


	namespace Key
	{
		enum : uint16_t
		{
			Space              = 32,
			Apostrophe         = 39,  /* ' */
			Comma              = 44,  /* , */
			Minus              = 45,  /* - */
			Period             = 46,  /* . */
			Slash              = 47,  /* / */
			N0                 = 48,
			N1                 = 49,
			N2                 = 50,
			N3                 = 51,
			N4                 = 52,
			N5                 = 53,
			N6                 = 54,
			N7                 = 55,
			N8                 = 56,
			N9                 = 57,
			Semicolon          = 59,  /* ; */
			Equal              = 61,  /* = */
			A                  = 65,
			B                  = 66,
			C                  = 67,
			D                  = 68,
			E                  = 69,
			F                  = 70,
			G                  = 71,
			H                  = 72,
			I                  = 73,
			J                  = 74,
			K                  = 75,
			L                  = 76,
			M                  = 77,
			N                  = 78,
			O                  = 79,
			P                  = 80,
			Q                  = 81,
			R                  = 82,
			S                  = 83,
			T                  = 84,
			U                  = 85,
			V                  = 86,
			W                  = 87,
			X                  = 88,
			Y                  = 89,
			Z                  = 90,
			LeftBracket        = 91,  /* [ */
			Backslash          = 92,  /* \ */
			RightBracket       = 93,  /* ] */
			GraveAccent        = 96,  /* ` */
			World1             = 161, /* non-US #1 */
			World2             = 162, /* non-US #2 */
			
			/* Function keys */
			Escape             = 256,
			Enter              = 257,
			Tab                = 258,
			Backspace          = 259,
			Insert             = 260,
			Delete             = 261,
			Right              = 262,
			Left               = 263,
			Down               = 264,
			Up                 = 265,
			PageUp             = 266,
			PageDown           = 267,
			Home               = 268,
			End                = 269,
			CapsLock           = 280,
			ScrollLock         = 281,
			NumLock            = 282,
			PrintScreen        = 283,
			Pause              = 284,
			F1                 = 290,
			F2                 = 291,
			F3                 = 292,
			F4                 = 293,
			F5                 = 294,
			F6                 = 295,
			F7                 = 296,
			F8                 = 297,
			F9                 = 298,
			F10                = 299,
			F11                = 300,
			F12                = 301,
			F13                = 302,
			F14                = 303,
			F15                = 304,
			F16                = 305,
			F17                = 306,
			F18                = 307,
			F19                = 308,
			F20                = 309,
			F21                = 310,
			F22                = 311,
			F23                = 312,
			F24                = 313,
			F25                = 314,
			Kp0                = 320,
			Kp1                = 321,
			Kp2                = 322,
			Kp3                = 323,
			Kp4                = 324,
			Kp5                = 325,
			Kp6                = 326,
			Kp7                = 327,
			Kp8                = 328,
			Kp9                = 329,
			KpDecimal          = 330,
			KpDivide           = 331,
			KpMultuply         = 332,
			KpSubtract         = 333,
			KpAdd              = 334,
			KpEnter            = 335,
			KpEqual            = 336,
			LeftShift          = 340,
			LeftCtrl           = 341,
			LeftAlt            = 342,
			LeftSuper          = 343,
			Windows            = 343,
			LeftCommand        = 343,
			RightShift         = 344,
			RightCtrl          = 345,
			RightAlt           = 346,
			RightSuper         = 347,
			RightCommand       = 347,
			Menu               = 348,
			
			Last               = Menu
		};
	}

}