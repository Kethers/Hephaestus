#include <Hephaestus.h>

#include <imgui/imgui.h>

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

		std::shared_ptr<Hep::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Hep::VertexBuffer::Create(vertices, sizeof(vertices)));
		Hep::BufferLayout layout = {
			{ Hep::ShaderDataType::Float3, "a_Position" },
			{ Hep::ShaderDataType::Float4, "a_Color" },
			// { ShaderDataType::Float3, "a_Normal" },
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[] = { 0, 1, 2 };
		std::shared_ptr<Hep::IndexBuffer> indexBuffer;
		indexBuffer.reset(Hep::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Hep::VertexArray::Create());
		float squareVertices[] = {
			-0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.75f, 0.75f, 0.0f,
			-0.75f, 0.75f, 0.0f,
		};
		std::shared_ptr<Hep::VertexBuffer> squareVB;
		squareVB.reset(Hep::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({ { Hep::ShaderDataType::Float3, "a_Position" } });
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Hep::IndexBuffer> squareIB;
		squareIB.reset(Hep::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		m_Shader.reset(new Hep::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Hep::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate() override
	{
		if (Hep::Input::IsKeyPressed(HEP_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed;
		else if (Hep::Input::IsKeyPressed(HEP_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed;

		if (Hep::Input::IsKeyPressed(HEP_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed;
		else if (Hep::Input::IsKeyPressed(HEP_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed;

		if (Hep::Input::IsKeyPressed(HEP_KEY_A))
			m_CameraRotation += m_CameraRotateSpeed;
		else if (Hep::Input::IsKeyPressed(HEP_KEY_D))
			m_CameraRotation -= m_CameraRotateSpeed;

		Hep::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hep::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Hep::Renderer::BeginScene(m_Camera);

		Hep::Renderer::Submit(m_BlueShader, m_SquareVA);
		Hep::Renderer::Submit(m_Shader, m_VertexArray);

		Hep::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{ }

	void OnEvent(Hep::Event& event) override
	{ }

private:
	std::shared_ptr<Hep::Shader> m_Shader;
	std::shared_ptr<Hep::VertexArray> m_VertexArray;

	std::shared_ptr<Hep::Shader> m_BlueShader;
	std::shared_ptr<Hep::VertexArray> m_SquareVA;

	Hep::OrthographicCamera m_Camera;
	rtm::float3f m_CameraPosition;
	float m_CameraMoveSpeed = 0.1f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotateSpeed = 2.0f;
};

class Sandbox : public Hep::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{ }
};

Hep::Application* Hep::CreateApplication()
{
	return new Sandbox{};
}
