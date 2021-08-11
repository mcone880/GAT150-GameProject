#pragma once
#include "Framework/System.h"
#include "Math/Vector2.h"
#include <vector>
#include <array>
#include <SDL_stdinc.h>

namespace MAC {

	class InputSystem : public System {
	public:

		enum class eKeyState {
			Idle,
			Pressed,
			Held,
			Release
		};

		enum class eMouseButton {
			Left,
			Middle,
			Right
		};

		void Startup() override;
		void Shutdown() override;
		void Update(float dt) override;

		eKeyState GetKeyState(int id);
		bool IsKeyDown(int id) const { return keyboardState[id]; }
		bool IsPreviousKeyDown(int id) const { return prevKeyboardState[id]; }

		const Vector2& GetMousePosition() const { return mousePosition; }
		bool IsButtonDown(int id) const { return mouseButtonState[id]; }
		bool IsPreviousButtonDown(int id) const { return prevMouseButtonState[id]; }
		eKeyState GetButtonState(int id);


	private:
		std::vector<Uint8> keyboardState;
		std::vector<Uint8> prevKeyboardState;
		int numKeys;

		Vector2 mousePosition;
		std::array<Uint8, 3> mouseButtonState;
		std::array<Uint8, 3> prevMouseButtonState;
	};
}