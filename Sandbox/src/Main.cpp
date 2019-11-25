
#include "Engine.h"

class SandboxState : public Engine::StateBase {
public:
	SandboxState() {

		Engine::App::Get()->OnWindowBufferSwap.Add(
		
			[](Engine::WindowBufferSwapEventArgs) {
				Log("Test", Engine::Settings::Get()->i++);
			}
		
		);
		
		Engine::App::Get()->OnWindowBufferSwap.Add(&SandboxState::OnWindowBufferSwap, this);

	}

	virtual void Update(Engine::TimeStamp dt) override {
	
		Log("Updating", "SandboxState");

	}
	virtual void Render(Engine::TimeStamp dt) override {

		Log("Rendering", "SandboxState");
	}

	void OnWindowBufferSwap(Engine::WindowBufferSwapEventArgs args) {
		Log("Buffer Swapped");
	}
};

void main() {

	Engine::App::Init()->Run<SandboxState>();

}