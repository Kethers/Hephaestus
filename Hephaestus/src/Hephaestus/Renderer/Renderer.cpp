#include "heppch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Hep
{
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;
	Renderer* Renderer::s_Instance = new Renderer();

	void Renderer::Clear() {}

	void Renderer::Clear(float r, float g, float b, float a)
	{
		HEP_RENDER_4(r, g, b, a, {
			RendererAPI::Clear(r,g,b,a);
			});
	}

	void Renderer::SetClearColor(float r, float g, float b, float a) {}

	void Renderer::ClearMagenta()
	{
		Clear(1, 0, 1);
	}

	void Renderer::WaitAndRender()
	{
		s_Instance->m_CommandQueue.Execute();
	}

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{ }

	void Renderer::Submit(const Ref<Shader>& shader,
		const Ref<VertexArray>& vertexArray,
		rtm::matrix4x4f_argn transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection",
			s_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
