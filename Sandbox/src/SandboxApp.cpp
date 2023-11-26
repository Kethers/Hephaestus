#include <Hephaestus.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include <imgui/imgui.h>

#include "rtm/matrix3x3d.h"
#include "rtm/matrix3x4f.h"

class ExampleLayer : public Hep::Layer
{
public:
	ExampleLayer()
		: Layer("Example"),
		  m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
		  m_CameraPosition({ 0.0f, 0.0f, 0.0f })
	{
		m_VertexArray.reset(Hep::VertexArray::Create());

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.7f, 0.2f, 1.0f,
		};

		Hep::Ref<Hep::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Hep::VertexBuffer::Create(vertices, sizeof(vertices)));
		Hep::BufferLayout layout = {
			{ Hep::ShaderDataType::Float3, "a_Position" },
			{ Hep::ShaderDataType::Float4, "a_Color" },
			// { ShaderDataType::Float3, "a_Normal" },
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[] = { 0, 1, 2 };
		Hep::Ref<Hep::IndexBuffer> indexBuffer;
		indexBuffer.reset(Hep::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Hep::VertexArray::Create());
		float squareVertices[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		};
		Hep::Ref<Hep::VertexBuffer> squareVB;
		squareVB.reset(Hep::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Hep::ShaderDataType::Float3, "a_Position" },
			{ Hep::ShaderDataType::Float2, "a_TexCoord" },
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[] = { 0, 1, 2, 2, 3, 0 };
		Hep::Ref<Hep::IndexBuffer> squareIB;
		squareIB.reset(Hep::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(Hep::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset(Hep::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

		std::string textureShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec2 v_TexCoord;
			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";
		std::string textureShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec2 v_TexCoord;
			
			uniform sampler2D u_Texture;
			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";
		m_TextureShader.reset(Hep::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));
		m_Texture = Hep::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = Hep::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Hep::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Hep::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Hep::Timestep ts) override
	{
		HEP_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		if (Hep::Input::IsKeyPressed(HEP_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Hep::Input::IsKeyPressed(HEP_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Hep::Input::IsKeyPressed(HEP_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Hep::Input::IsKeyPressed(HEP_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Hep::Input::IsKeyPressed(HEP_KEY_A))
			m_CameraRotation += m_CameraRotateSpeed * ts;
		else if (Hep::Input::IsKeyPressed(HEP_KEY_D))
			m_CameraRotation -= m_CameraRotateSpeed * ts;

		Hep::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hep::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Hep::Renderer::BeginScene(m_Camera);

		static rtm::float3f scale{ 0.1f, 0.1f, 0.1f };

		rtm::float4f redColor(0.8f, 0.2f, 0.3f, 1.0f);
		rtm::float4f blueColor(0.2f, 0.3f, 0.8f, 1.0f);

		std::dynamic_pointer_cast<Hep::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Hep::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);
		for (int i = 0; i < 20; ++i)
		{
			for (int j = 0; j < 20; ++j)
			{
				rtm::float3f pos(i * 0.11f, j * 0.11f, 0.0f);
				rtm::matrix3x4f transform = rtm::matrix_from_qvv(rtm::quat_identity(),
					rtm::vector_load3(&pos),
					rtm::vector_load3(&scale));
				Hep::Renderer::Submit(m_FlatColorShader, m_SquareVA, matrix_cast(transform));
			}
		}

		m_Texture->Bind();
		Hep::Renderer::Submit(m_TextureShader, m_SquareVA,
			rtm::matrix_cast<rtm::matrix3x4f>(rtm::matrix_from_scale(rtm::vector_load(new rtm::float4f(1.5f)))));
		m_ChernoLogoTexture->Bind();
		Hep::Renderer::Submit(m_TextureShader, m_SquareVA,
			rtm::matrix_cast<rtm::matrix3x4f>(rtm::matrix_from_scale(rtm::vector_load(new rtm::float4f(1.5f)))));

		// Triangle
		// Hep::Renderer::Submit(m_Shader, m_VertexArray);

		Hep::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", (float*)&m_SquareColor);
		ImGui::End();
	}

	void OnEvent(Hep::Event& event) override
	{ }

private:
	Hep::Ref<Hep::Shader> m_Shader;
	Hep::Ref<Hep::VertexArray> m_VertexArray;

	Hep::Ref<Hep::Shader> m_FlatColorShader, m_TextureShader;
	Hep::Ref<Hep::VertexArray> m_SquareVA;

	Hep::Ref<Hep::Texture2D> m_Texture, m_ChernoLogoTexture;

	Hep::OrthographicCamera m_Camera;
	rtm::float3f m_CameraPosition;
	rtm::float3f m_SquareColor{ 0.8f, 0.2f, 0.3f };
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotateSpeed = 180.0f;
};

class Sandbox : public Hep::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox() override = default;
};

Hep::Application* Hep::CreateApplication()
{
	return new Sandbox{};
}
