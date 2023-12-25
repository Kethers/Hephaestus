#pragma once

#include "Hephaestus/Renderer/Pipeline.h"

namespace Hep
{
	class OpenGLPipeline : public Pipeline
	{
	public:
		OpenGLPipeline(const PipelineSpecification& spec);
		~OpenGLPipeline() override;

		virtual PipelineSpecification& GetSpecification() { return m_Specification; }
		virtual const PipelineSpecification& GetSpecification() const { return m_Specification; }

		void Invalidate() override;

		void Bind() override;

	private:
		PipelineSpecification m_Specification;
		uint32_t m_VertexArrayRendererID = 0;
	};
}
