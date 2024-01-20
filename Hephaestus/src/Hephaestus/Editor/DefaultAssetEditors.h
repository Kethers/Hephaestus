#pragma once

#include "AssetEditorPanel.h"
#include "Hephaestus/Renderer/Mesh.h"

namespace Hep
{
	class PhysicsMaterialEditor : public AssetEditor
	{
	public:
		PhysicsMaterialEditor();

		void SetAsset(const Ref<Asset>& asset) override { m_Asset = (Ref<PhysicsMaterial>)asset; }

	private:
		void OnClose() override;
		void Render() override;

	private:
		Ref<PhysicsMaterial> m_Asset;
	};

	class TextureViewer : public AssetEditor
	{
	public:
		TextureViewer();

		void SetAsset(const Ref<Asset>& asset) override { m_Asset = (Ref<Texture>)asset; }

	private:
		void OnClose() override;
		void Render() override;

	private:
		Ref<Texture> m_Asset;
	};
}
