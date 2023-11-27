#pragma once

#include "heppch.h"

namespace Hep
{
	class HEP_API RenderCommandQueue
	{
	public:
		using RenderCommandFn = void(*)(void*);

		RenderCommandQueue();
		~RenderCommandQueue();

		void* Allocate(RenderCommandFn func, unsigned int size);

		void Execute();

	private:
		unsigned char* m_CommandBuffer;
		unsigned char* m_CommandBufferPtr;
		unsigned int m_CommandCount = 0;
	};
}
