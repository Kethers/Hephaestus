#pragma once

#include "Hephaestus/Renderer/RendererAPI.h"

namespace Hep
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void SetClearColor(const rtm::float4f& color) override;
		void Clear() override;
		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

	private:
	};
}
