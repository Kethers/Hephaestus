﻿#pragma once

#include "Hephaestus/Renderer/RenderPass.h"

namespace Hep
{
	class OpenGLRenderPass : public RenderPass
	{
	public:
		OpenGLRenderPass(const RenderPassSpecification& spec);
		~OpenGLRenderPass() override;

		const RenderPassSpecification& GetSpecification() const override { return m_Specification; }

	private:
		RenderPassSpecification m_Specification;
	};
}
