#pragma once

#include "Hephaestus/Renderer/VertexArray.h"

namespace Hep
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void Bind() const override;
		void Unbind() const override;

		void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		const std::vector<Ref<VertexBuffer>>& GetVertexBuffer() const override { return m_Vertexbuffers; }
		const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_Indexbuffer; }

	private:
		uint32_t m_RendererID;
		std::vector<Ref<VertexBuffer>> m_Vertexbuffers;
		Ref<IndexBuffer> m_Indexbuffer;
	};
}
