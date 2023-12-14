#pragma once

namespace Hep
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space      = 32,
		Apostrophe = 39, /* ' */
		Comma      = 44, /* , */
		Minus      = 45, /* - */
		Period     = 46, /* . */
		Slash      = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal     = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket  = 91, /* [ */
		Backslash    = 92, /* \ */
		RightBracket = 93, /* ] */
		GraveAccent  = 96, /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape      = 256,
		Enter       = 257,
		Tab         = 258,
		Backspace   = 259,
		Insert      = 260,
		Delete      = 261,
		Right       = 262,
		Left        = 263,
		Down        = 264,
		Up          = 265,
		PageUp      = 266,
		PageDown    = 267,
		Home        = 268,
		End         = 269,
		CapsLock    = 280,
		ScrollLock  = 281,
		NumLock     = 282,
		PrintScreen = 283,
		Pause       = 284,
		F1          = 290,
		F2          = 291,
		F3          = 292,
		F4          = 293,
		F5          = 294,
		F6          = 295,
		F7          = 296,
		F8          = 297,
		F9          = 298,
		F10         = 299,
		F11         = 300,
		F12         = 301,
		F13         = 302,
		F14         = 303,
		F15         = 304,
		F16         = 305,
		F17         = 306,
		F18         = 307,
		F19         = 308,
		F20         = 309,
		F21         = 310,
		F22         = 311,
		F23         = 312,
		F24         = 313,
		F25         = 314,

		/* Keypad */
		KP0        = 320,
		KP1        = 321,
		KP2        = 322,
		KP3        = 323,
		KP4        = 324,
		KP5        = 325,
		KP6        = 326,
		KP7        = 327,
		KP8        = 328,
		KP9        = 329,
		KPDecimal  = 330,
		KPDivide   = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd      = 334,
		KPEnter    = 335,
		KPEqual    = 336,

		LeftShift    = 340,
		LeftControl  = 341,
		LeftAlt      = 342,
		LeftSuper    = 343,
		RightShift   = 344,
		RightControl = 345,
		RightAlt     = 346,
		RightSuper   = 347,
		Menu         = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define HEP_KEY_SPACE           ::Hep::Key::Space
#define HEP_KEY_APOSTROPHE      ::Hep::Key::Apostrophe    /* ' */
#define HEP_KEY_COMMA           ::Hep::Key::Comma         /* , */
#define HEP_KEY_MINUS           ::Hep::Key::Minus         /* - */
#define HEP_KEY_PERIOD          ::Hep::Key::Period        /* . */
#define HEP_KEY_SLASH           ::Hep::Key::Slash         /* / */
#define HEP_KEY_0               ::Hep::Key::D0
#define HEP_KEY_1               ::Hep::Key::D1
#define HEP_KEY_2               ::Hep::Key::D2
#define HEP_KEY_3               ::Hep::Key::D3
#define HEP_KEY_4               ::Hep::Key::D4
#define HEP_KEY_5               ::Hep::Key::D5
#define HEP_KEY_6               ::Hep::Key::D6
#define HEP_KEY_7               ::Hep::Key::D7
#define HEP_KEY_8               ::Hep::Key::D8
#define HEP_KEY_9               ::Hep::Key::D9
#define HEP_KEY_SEMICOLON       ::Hep::Key::Semicolon     /* ; */
#define HEP_KEY_EQUAL           ::Hep::Key::Equal         /* = */
#define HEP_KEY_A               ::Hep::Key::A
#define HEP_KEY_B               ::Hep::Key::B
#define HEP_KEY_C               ::Hep::Key::C
#define HEP_KEY_D               ::Hep::Key::D
#define HEP_KEY_E               ::Hep::Key::E
#define HEP_KEY_F               ::Hep::Key::F
#define HEP_KEY_G               ::Hep::Key::G
#define HEP_KEY_H               ::Hep::Key::H
#define HEP_KEY_I               ::Hep::Key::I
#define HEP_KEY_J               ::Hep::Key::J
#define HEP_KEY_K               ::Hep::Key::K
#define HEP_KEY_L               ::Hep::Key::L
#define HEP_KEY_M               ::Hep::Key::M
#define HEP_KEY_N               ::Hep::Key::N
#define HEP_KEY_O               ::Hep::Key::O
#define HEP_KEY_P               ::Hep::Key::P
#define HEP_KEY_Q               ::Hep::Key::Q
#define HEP_KEY_R               ::Hep::Key::R
#define HEP_KEY_S               ::Hep::Key::S
#define HEP_KEY_T               ::Hep::Key::T
#define HEP_KEY_U               ::Hep::Key::U
#define HEP_KEY_V               ::Hep::Key::V
#define HEP_KEY_W               ::Hep::Key::W
#define HEP_KEY_X               ::Hep::Key::X
#define HEP_KEY_Y               ::Hep::Key::Y
#define HEP_KEY_Z               ::Hep::Key::Z
#define HEP_KEY_LEFT_BRACKET    ::Hep::Key::LeftBracket   /* [ */
#define HEP_KEY_BACKSLASH       ::Hep::Key::Backslash     /* \ */
#define HEP_KEY_RIGHT_BRACKET   ::Hep::Key::RightBracket  /* ] */
#define HEP_KEY_GRAVE_ACCENT    ::Hep::Key::GraveAccent   /* ` */
#define HEP_KEY_WORLD_1         ::Hep::Key::World1        /* non-US #1 */
#define HEP_KEY_WORLD_2         ::Hep::Key::World2        /* non-US #2 */

/* Function keys */
#define HEP_KEY_ESCAPE          ::Hep::Key::Escape
#define HEP_KEY_ENTER           ::Hep::Key::Enter
#define HEP_KEY_TAB             ::Hep::Key::Tab
#define HEP_KEY_BACKSPACE       ::Hep::Key::Backspace
#define HEP_KEY_INSERT          ::Hep::Key::Insert
#define HEP_KEY_DELETE          ::Hep::Key::Delete
#define HEP_KEY_RIGHT           ::Hep::Key::Right
#define HEP_KEY_LEFT            ::Hep::Key::Left
#define HEP_KEY_DOWN            ::Hep::Key::Down
#define HEP_KEY_UP              ::Hep::Key::Up
#define HEP_KEY_PAGE_UP         ::Hep::Key::PageUp
#define HEP_KEY_PAGE_DOWN       ::Hep::Key::PageDown
#define HEP_KEY_HOME            ::Hep::Key::Home
#define HEP_KEY_END             ::Hep::Key::End
#define HEP_KEY_CAPS_LOCK       ::Hep::Key::CapsLock
#define HEP_KEY_SCROLL_LOCK     ::Hep::Key::ScrollLock
#define HEP_KEY_NUM_LOCK        ::Hep::Key::NumLock
#define HEP_KEY_PRINT_SCREEN    ::Hep::Key::PrintScreen
#define HEP_KEY_PAUSE           ::Hep::Key::Pause
#define HEP_KEY_F1              ::Hep::Key::F1
#define HEP_KEY_F2              ::Hep::Key::F2
#define HEP_KEY_F3              ::Hep::Key::F3
#define HEP_KEY_F4              ::Hep::Key::F4
#define HEP_KEY_F5              ::Hep::Key::F5
#define HEP_KEY_F6              ::Hep::Key::F6
#define HEP_KEY_F7              ::Hep::Key::F7
#define HEP_KEY_F8              ::Hep::Key::F8
#define HEP_KEY_F9              ::Hep::Key::F9
#define HEP_KEY_F10             ::Hep::Key::F10
#define HEP_KEY_F11             ::Hep::Key::F11
#define HEP_KEY_F12             ::Hep::Key::F12
#define HEP_KEY_F13             ::Hep::Key::F13
#define HEP_KEY_F14             ::Hep::Key::F14
#define HEP_KEY_F15             ::Hep::Key::F15
#define HEP_KEY_F16             ::Hep::Key::F16
#define HEP_KEY_F17             ::Hep::Key::F17
#define HEP_KEY_F18             ::Hep::Key::F18
#define HEP_KEY_F19             ::Hep::Key::F19
#define HEP_KEY_F20             ::Hep::Key::F20
#define HEP_KEY_F21             ::Hep::Key::F21
#define HEP_KEY_F22             ::Hep::Key::F22
#define HEP_KEY_F23             ::Hep::Key::F23
#define HEP_KEY_F24             ::Hep::Key::F24
#define HEP_KEY_F25             ::Hep::Key::F25

/* Keypad */
#define HEP_KEY_KP_0            ::Hep::Key::KP0
#define HEP_KEY_KP_1            ::Hep::Key::KP1
#define HEP_KEY_KP_2            ::Hep::Key::KP2
#define HEP_KEY_KP_3            ::Hep::Key::KP3
#define HEP_KEY_KP_4            ::Hep::Key::KP4
#define HEP_KEY_KP_5            ::Hep::Key::KP5
#define HEP_KEY_KP_6            ::Hep::Key::KP6
#define HEP_KEY_KP_7            ::Hep::Key::KP7
#define HEP_KEY_KP_8            ::Hep::Key::KP8
#define HEP_KEY_KP_9            ::Hep::Key::KP9
#define HEP_KEY_KP_DECIMAL      ::Hep::Key::KPDecimal
#define HEP_KEY_KP_DIVIDE       ::Hep::Key::KPDivide
#define HEP_KEY_KP_MULTIPLY     ::Hep::Key::KPMultiply
#define HEP_KEY_KP_SUBTRACT     ::Hep::Key::KPSubtract
#define HEP_KEY_KP_ADD          ::Hep::Key::KPAdd
#define HEP_KEY_KP_ENTER        ::Hep::Key::KPEnter
#define HEP_KEY_KP_EQUAL        ::Hep::Key::KPEqual

#define HEP_KEY_LEFT_SHIFT      ::Hep::Key::LeftShift
#define HEP_KEY_LEFT_CONTROL    ::Hep::Key::LeftControl
#define HEP_KEY_LEFT_ALT        ::Hep::Key::LeftAlt
#define HEP_KEY_LEFT_SUPER      ::Hep::Key::LeftSuper
#define HEP_KEY_RIGHT_SHIFT     ::Hep::Key::RightShift
#define HEP_KEY_RIGHT_CONTROL   ::Hep::Key::RightControl
#define HEP_KEY_RIGHT_ALT       ::Hep::Key::RightAlt
#define HEP_KEY_RIGHT_SUPER     ::Hep::Key::RightSuper
#define HEP_KEY_MENU            ::Hep::Key::Menu
