#pragma once

#include "Hephaestus/Layer.h"
#include "Hephaestus/Events/ApplicationEvent.h"
#include "Hephaestus/Events/KeyEvent.h"
#include "Hephaestus/Events/MouseEvent.h"

namespace Hep
{
	class HEP_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time;
	};
}
