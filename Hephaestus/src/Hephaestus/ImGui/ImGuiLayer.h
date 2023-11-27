#pragma once

#include "Hephaestus/Core/Layer.h"
#include "Hephaestus/Core/Events/ApplicationEvent.h"
#include "Hephaestus/Core/Events/KeyEvent.h"
#include "Hephaestus/Core/Events/MouseEvent.h"

namespace Hep
{
	class HEP_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		ImGuiLayer(const std::string& name);
		~ImGuiLayer() override = default;

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time;
	};
}
