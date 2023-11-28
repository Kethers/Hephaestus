#pragma once

#include "Hephaestus/Renderer/Buffer.h"

namespace Hep
{
	class HEP_API OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(unsigned int size);
		~OpenGLVertexBuffer() override;

		void SetData(void* buffer, unsigned int size, unsigned int offset = 0) override;
		void Bind() const override;

		unsigned int GetSize() const override { return m_Size; }
		RendererID GetRendererID() const override { return m_RendererID; }

	private:
		RendererID m_RendererID;
		unsigned int m_Size;
	};

	class HEP_API OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int size);
		~OpenGLIndexBuffer() override;

		void SetData(void* buffer, unsigned int size, unsigned int offset = 0) override;
		void Bind() const override;

		uint32_t GetCount() const override { return m_Size / sizeof(uint32_t); }

		unsigned int GetSize() const override { return m_Size; }
		RendererID GetRendererID() const override { return m_RendererID; }

	private:
		RendererID m_RendererID;
		unsigned int m_Size;
	};
}
