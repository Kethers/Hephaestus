#pragma once

#include "Hephaestus/Renderer/RendererAPI.h"

namespace Hep
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void Init() override;

		void SetClearColor(const rtm::float4f& color) override;
		void Clear() override;
		void DrawIndexed(const Ref<VertexArray>& vertexArray) override;

	private:
	};
}
