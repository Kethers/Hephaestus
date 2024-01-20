#pragma once

#include "Hephaestus/ImGui/ImGuiLayer.h"

namespace Hep
{
	class OpenGLImGuiLayer : public ImGuiLayer
	{
	public:
		OpenGLImGuiLayer();
		OpenGLImGuiLayer(const std::string& name);
		~OpenGLImGuiLayer() override;

		void Begin() override;
		void End() override;

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

	private:
		float m_Time = 0.0f;
	};
}
