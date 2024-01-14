#pragma once

#include "Hephaestus/Renderer/Texture.h"
#include "Hephaestus/Asset/AssetManager.h"

namespace Hep
{
	class ObjectsPanel
	{
	public:
		ObjectsPanel();

		void OnImGuiRender();

	private:
		void DrawObject(const char* label, AssetHandle handle);

	private:
		Ref<Texture2D> m_CubeImage;
	};
}
