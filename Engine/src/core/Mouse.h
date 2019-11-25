#pragma once

namespace Engine
{
	enum class MouseButton {

		MOUSE_BUTTON_1 = 0,
		MOUSE_BUTTON_2 = 1,
		MOUSE_BUTTON_3 = 2,
		MOUSE_BUTTON_4 = 3,
		MOUSE_BUTTON_5 = 4,
		MOUSE_BUTTON_6 = 5,
		MOUSE_BUTTON_7 = 6,
		MOUSE_BUTTON_8 = 7,
		MOUSE_BUTTON_LAST = MOUSE_BUTTON_8,
		MOUSE_BUTTON_LEFT = MOUSE_BUTTON_1,
		MOUSE_BUTTON_RIGHT = MOUSE_BUTTON_2,
		MOUSE_BUTTON_MIDDLE = MOUSE_BUTTON_3
	};

	class Mouse {

		static bool IsButtonPressed(MouseButton b);
		static bool IsButtonReleased(MouseButton b);

	};

	struct MouseButtonPressedEventArgs {

		int clicks;
		MouseButton button;
	};
	struct MouseButtonReleasedEventArgs {

		MouseButton button;
	};

	struct MouseMovedEventArgs {

		int x, y, dx, dy;
	};
}