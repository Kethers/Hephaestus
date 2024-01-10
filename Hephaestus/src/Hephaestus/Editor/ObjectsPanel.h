#pragma once

#include "Hephaestus/Renderer/Texture.h"

namespace Hep
{
	class ObjectsPanel
	{
	public:
		ObjectsPanel();

		void OnImGuiRender();

	private:
		Ref<Texture2D> m_CubeImage;
	};
}
