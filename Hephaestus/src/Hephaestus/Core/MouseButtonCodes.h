#pragma once

namespace Hep
{
	typedef enum class MouseButton : uint16_t
	{
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Left    = Button0,
		Right   = Button1,
		Middle  = Button2
	} Button;

	inline std::ostream& operator<<(std::ostream& os, MouseButton button)
	{
		os << static_cast<int32_t>(button);
		return os;
	}
}

// From glfw3.h
#define HEP_MOUSE_BUTTON_1         0
#define HEP_MOUSE_BUTTON_2         1
#define HEP_MOUSE_BUTTON_3         2
#define HEP_MOUSE_BUTTON_4         3
#define HEP_MOUSE_BUTTON_5         4
#define HEP_MOUSE_BUTTON_6         5
#define HEP_MOUSE_BUTTON_7         6
#define HEP_MOUSE_BUTTON_8         7
#define HEP_MOUSE_BUTTON_LAST      HEP_MOUSE_BUTTON_8
#define HEP_MOUSE_BUTTON_LEFT      HEP_MOUSE_BUTTON_1
#define HEP_MOUSE_BUTTON_RIGHT     HEP_MOUSE_BUTTON_2
#define HEP_MOUSE_BUTTON_MIDDLE    HEP_MOUSE_BUTTON_3
