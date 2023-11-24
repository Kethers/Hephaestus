#pragma once

#include "OrthographicCamera.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "rtm/impl/matrix_common.h"

namespace Hep
{
	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const ::std::shared_ptr<Shader>& shader,
			const std::shared_ptr<VertexArray>& vertexArray,
			const rtm::matrix4x4f& transform = rtm::matrix_identity());

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			rtm::matrix4x4f ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};
}
