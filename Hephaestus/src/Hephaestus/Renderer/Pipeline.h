#pragma once

#include "Hephaestus/Core/Ref.h"

#include "Hephaestus/Renderer/VertexBuffer.h"
#include "Hephaestus/Renderer/Shader.h"

namespace Hep
{
	struct PipelineSpecification
	{
		Ref<Hep::Shader> Shader;
		VertexBufferLayout Layout;
	};

	class Pipeline : public RefCounted
	{
	public:
		virtual ~Pipeline() = default;

		virtual PipelineSpecification& GetSpecification() = 0;
		virtual const PipelineSpecification& GetSpecification() const = 0;

		virtual void Invalidate() = 0;

		// TEMP: remove this when render command buffers are a thing
		virtual void Bind() = 0;

		static Ref<Pipeline> Create(const PipelineSpecification& spec);
	};
}
