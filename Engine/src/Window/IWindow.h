#pragma once

#include "Defines.h"

namespace Engine
{
	class IWindow {

		static Ref<IWindow> Create(const String& title);

	};

	struct WindowResizeEventArgs {

		int width, height;
	};

	struct WindowMovedEventArgs {

		int x, y;
	};

	struct WindowMaximizedEventArgs {

	};

	struct WindowFocusChangedEventArgs {

		bool gainedFocus, lostFocus;
	};

	struct WindowBufferSwapEventArgs {

	};

}