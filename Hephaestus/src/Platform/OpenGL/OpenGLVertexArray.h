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

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() const override { return m_Vertexbuffers; }
		const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return m_Indexbuffer; }

	private:
		uint32_t m_RendererID;
		std::vector<std::shared_ptr<VertexBuffer>> m_Vertexbuffers;
		std::shared_ptr<IndexBuffer> m_Indexbuffer;
	};
}
