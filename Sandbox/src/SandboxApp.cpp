#include <Hephaestus.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include <imgui/imgui.h>

#include "rtm/matrix3x3d.h"
#include "rtm/matrix3x4f.h"

static void ImGuiShowHelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

class EditorLayer : public Hep::Layer
{
public:
	EditorLayer()
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

		m_Shader = Hep::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

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

		m_FlatColorShader = Hep::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);
		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Hep::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = Hep::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Hep::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Hep::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
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

		auto textureShader = m_ShaderLibrary.Get("Texture");
		m_Texture->Bind();
		Hep::Renderer::Submit(textureShader, m_SquareVA,
			rtm::matrix_cast<rtm::matrix3x4f>(rtm::matrix_from_scale(rtm::vector_load(new rtm::float4f(1.5f)))));
		m_ChernoLogoTexture->Bind();
		Hep::Renderer::Submit(textureShader, m_SquareVA,
			rtm::matrix_cast<rtm::matrix3x4f>(rtm::matrix_from_scale(rtm::vector_load(new rtm::float4f(1.5f)))));

		// Triangle
		// Hep::Renderer::Submit(m_Shader, m_VertexArray);

		Hep::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		static bool show_demo_window = true;
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		ImGui::Begin("EditorLayer");
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
		ImGui::End();

#if ENABLE_DOCKSPACE
		static bool p_open = true;

		static bool opt_fullscreen_persistant = true;
		static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
		bool opt_fullscreen = opt_fullscreen_persistant;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruDockspace, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (opt_flags & ImGuiDockNodeFlags_PassthruDockspace)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &p_open, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Dockspace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Docking"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Flag: NoSplit", "", (opt_flags & ImGuiDockNodeFlags_NoSplit) != 0))                 opt_flags ^= ImGuiDockNodeFlags_NoSplit;
				if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (opt_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0))  opt_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode;
				if (ImGui::MenuItem("Flag: NoResize", "", (opt_flags & ImGuiDockNodeFlags_NoResize) != 0))                opt_flags ^= ImGuiDockNodeFlags_NoResize;
				if (ImGui::MenuItem("Flag: PassthruDockspace", "", (opt_flags & ImGuiDockNodeFlags_PassthruDockspace) != 0))       opt_flags ^= ImGuiDockNodeFlags_PassthruDockspace;
				if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (opt_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))          opt_flags ^= ImGuiDockNodeFlags_AutoHideTabBar;
				ImGui::Separator();
				if (ImGui::MenuItem("Close DockSpace", NULL, false, p_open != NULL))
					p_open = false;
				ImGui::EndMenu();
			}
			ImGuiShowHelpMarker(
				"You can _always_ dock _any_ window into another by holding the SHIFT key while moving a window. Try it now!" "\n"
				"This demo app has nothing to do with it!" "\n\n"
				"This demo app only demonstrate the use of ImGui::DockSpace() which allows you to manually create a docking node _within_ another window. This is useful so you can decorate your main application window (e.g. with a menu bar)." "\n\n"
				"ImGui::DockSpace() comes with one hard constraint: it needs to be submitted _before_ any window which may be docked into it. Therefore, if you use a dock spot as the central point of your application, you'll probably want it to be part of the very first window you are submitting to imgui every frame." "\n\n"
				"(NB: because of this constraint, the implicit \"Debug\" window can not be docked into an explicit DockSpace() node, because that window is submitted as part of the NewFrame() call. An easy workaround is that you can create your own implicit \"Debug##2\" window after calling DockSpace() and leave it in the window stack for anyone to use.)"
			);

			ImGui::EndMenuBar();
		}

		ImGui::End();
#endif
	}

	void OnEvent(Hep::Event& event) override
	{ }

private:
	Hep::Ref<Hep::Shader> m_Shader;
	Hep::Ref<Hep::VertexArray> m_VertexArray;

	Hep::ShaderLibrary m_ShaderLibrary;
	Hep::Ref<Hep::Shader> m_FlatColorShader;
	Hep::Ref<Hep::VertexArray> m_SquareVA;

	Hep::Ref<Hep::Texture2D> m_Texture, m_ChernoLogoTexture;

	Hep::OrthographicCamera m_Camera;
	rtm::float3f m_CameraPosition;
	rtm::float3f m_SquareColor{ 0.8f, 0.2f, 0.3f };
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotateSpeed = 180.0f;

	float m_ClearColor[4];
};

class Sandbox : public Hep::Application
{
public:
	Sandbox()
	{ }

	void OnInit() override
	{
		PushLayer(new EditorLayer());
	}

	~Sandbox() override = default;
};

Hep::Application* Hep::CreateApplication()
{
	return new Sandbox{};
}
