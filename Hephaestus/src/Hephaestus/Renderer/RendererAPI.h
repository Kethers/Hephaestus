#pragma once

#include <rtm/math.h>

#include "VertexArray.h"

namespace Hep
{
	class RendererAPI
	{
	public:
		static void Clear(float r, float g, float b, float a);
		static void SetClearColor(float r, float g, float b, float a);

		#pragma region enums
		enum class API
		{
			None   = 0,
			OpenGL = 1,
		};
		#pragma endregion

		virtual void Init() = 0;
		virtual void SetClearColor(const rtm::float4f& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
}
