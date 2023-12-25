#pragma once

#include "Hephaestus/Core/Buffer.h"
#include "Hephaestus/Renderer/VertexBuffer.h"

namespace Hep
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(void* data, uint32_t size, VertexBufferUsage usage = VertexBufferUsage::Static);
		OpenGLVertexBuffer(uint32_t size, VertexBufferUsage usage = VertexBufferUsage::Dynamic);
		~OpenGLVertexBuffer() override;

		void SetData(void* data, uint32_t size, uint32_t offset = 0) override;
		void Bind() const override;

		const VertexBufferLayout& GetLayout() const override { return m_Layout; }
		void SetLayout(const VertexBufferLayout& layout) override { m_Layout = layout; }

		uint32_t GetSize() const override { return m_Size; }
		RendererID GetRendererID() const override { return m_RendererID; }

	private:
		RendererID m_RendererID = 0;
		uint32_t m_Size;
		VertexBufferUsage m_Usage;
		VertexBufferLayout m_Layout;

		Buffer m_LocalData;
	};
}
