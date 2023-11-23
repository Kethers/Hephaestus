#pragma once

#include "OrthographicCamera.h"
#include "RenderCommand.h"
#include "Shader.h"

namespace Hep
{
	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const ::std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			rtm::matrix4x4f ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}
