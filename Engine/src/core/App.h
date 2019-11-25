#pragma once

#include "Defines.h"
#include "Settings.h"
#include "Event.h"
#include "State.h"

#include "Time.h"
#include "Mouse.h"
#include "KeyBoard.h"

#include "Window/IWindow.h"

namespace Engine {

	class App;

	static Ref<App> privateStaticAppInstance = nullptr;

	class App {

#pragma region Static

	public:
		static inline Ref<App> Get() {
			if (privateStaticAppInstance == nullptr)
				throw std::exception("Application was not initialized! Call: Engine::App::Init()");
			return privateStaticAppInstance;
		}

		static Ref<App> Init() {

			if (privateStaticAppInstance != nullptr)
				throw std::exception("Application was allready initialized!");

			struct app_shared_enabler : public App {};

			privateStaticAppInstance = MakeRef<app_shared_enabler>();

			return Get();
		}

		template <typename T, typename... Args>
		static void Run(Args&&... args) {

			Get()->PushState<T>(std::forward<Args>(args)...);
			Get()->Loop();
		}

#pragma endregion

	private:
		App() {
			SettingSerilization::Load();
		}

		~App() {
			SettingSerilization::Save();
		}

		void Loop() {

			while (true) {

				auto& state = GetState();

				state.Update(0.1f);
				state.Render(0.1f);

				OnWindowBufferSwap({});
				break;
			}
		}

	public:

#pragma region States

		template <typename T, typename... Args>
		void PushState(Args&&... args) {
			m_States.push(MakeOwn<T>(std::forward<Args>(args)...));
		}
		void PopState() { m_PopState = true; }
		void PopAllStates() { m_PopAllStates = true; }

		StateBase& GetState() { return *m_States.top(); }

#pragma endregion

	public:

#pragma region Events

		Event<TimeStamp> OnImGuiRender;

		Event<WindowResizeEventArgs> OnWindowResize;
		Event<WindowMovedEventArgs> OnWindowMoved;
		Event<WindowMaximizedEventArgs> OnWindowMaximized;
		Event<WindowFocusChangedEventArgs> OnWindowFocusChanged;
		Event<WindowBufferSwapEventArgs> OnWindowBufferSwap;

		Event<KeyPressedEventArgs> OnKeyPressed;
		Event<KeyReleasedEventArgs> OnKeyReleased;

		Event<MouseMovedEventArgs> OnMouseMoved;
		Event<MouseButtonPressedEventArgs> OnMouseButtonPressed;
		Event<MouseButtonReleasedEventArgs> OnMouseButtonReleased;

#pragma endregion

	private:
		Own<IWindow> m_Window;
		Stack<Own<StateBase>> m_States;
		bool m_PopState = false, m_PopAllStates = false;
	};
}