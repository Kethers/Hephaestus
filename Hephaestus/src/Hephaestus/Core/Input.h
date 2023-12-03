#pragma once

namespace Hep
{
	class Input
	{
	protected:
		Input() = default;
		Input(const Input& input) = delete;
		Input& operator=(const Input&) = delete;

	public:
		static bool IsKeyPressed(int keycode);
		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}
