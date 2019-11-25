#include "IWindow.h"

#include "Settings.h"
#include "Window/Window.h"

namespace Engine
{
	Ref<IWindow> IWindow::Create(const String& title) {

		switch (Settings::Get()->ActiveOS)
		{
		case OS::Windows:	return MakeRef<Window>(title);
		case OS::Mac:
		case OS::Linux:
		case OS::Unknown:
			LogError("Unsupported Operating System to create Window!");
			break;
		}
		return nullptr;
	}
}
