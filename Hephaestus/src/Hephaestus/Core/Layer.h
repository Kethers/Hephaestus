#pragma once

#include "Hephaestus/Core/TimeStep.h"
#include "Base.h"
#include "Hephaestus/Core/Events/Event.h"

namespace Hep
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() { }

		virtual void OnDetach() { }

		virtual void OnUpdate(TimeStep ts) { }

		virtual void OnImGuiRender() { }

		virtual void OnEvent(Event& event) { }

		const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}
