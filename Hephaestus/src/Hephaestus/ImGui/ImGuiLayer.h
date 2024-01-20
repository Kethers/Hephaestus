#pragma once

#include "Hephaestus/Core/Layer.h"

namespace Hep
{
	class ImGuiLayer : public Layer
	{
	public:
		virtual void Begin() = 0;
		virtual void End() = 0;

		void SetDarkThemeColors();

		static ImGuiLayer* Create();
	};
}
