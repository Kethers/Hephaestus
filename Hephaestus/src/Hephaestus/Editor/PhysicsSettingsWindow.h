#pragma once

namespace Hep
{
	class PhysicsSettingsWindow
	{
	public:
		static void OnImGuiRender(bool* show);
		static void RenderLayerList();
		static void RenderSelectedLayer();
	};
}
