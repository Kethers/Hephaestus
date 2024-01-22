﻿#pragma once

#include "Hephaestus/Renderer/RendererAPI.h"

namespace Hep
{
	class VulkanRenderer : public RendererAPI
	{
	public:
		void Init() override;
		void Shutdown() override;

		RendererCapabilities& GetCapabilities() override;

		void BeginFrame() override;
		void EndFrame() override;

		void BeginRenderPass(const Ref<RenderPass>& renderPass) override;
		void EndRenderPass() override;
		void SubmitFullscreenQuad(Ref<Pipeline> pipeline, Ref<Material> material) override;

		void SetSceneEnvironment(Ref<Environment> environment, Ref<Image2D> shadow) override;
		std::pair<Ref<TextureCube>, Ref<TextureCube>> CreateEnvironmentMap(const std::string& filepath) override;
		Ref<TextureCube> CreatePreethamSky(float turbidity, float azimuth, float inclination) override;

		void RenderMesh(Ref<Pipeline> pipeline, Ref<Mesh> mesh, const glm::mat4& transform) override;
		void RenderMeshWithoutMaterial(Ref<Pipeline> pipeline, Ref<Mesh> mesh, const glm::mat4& transform) override;
		void RenderQuad(Ref<Pipeline> pipeline, Ref<Material> material, const glm::mat4& transform) override;
	};
}
