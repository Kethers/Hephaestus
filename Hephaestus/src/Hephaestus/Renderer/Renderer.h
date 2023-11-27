#pragma once

#include "OrthographicCamera.h"
#include "RenderCommand.h"
#include "RenderCommandQueue.h"
#include "Shader.h"
#include "rtm/impl/matrix_common.h"

namespace Hep
{
	class Renderer
	{
	public:
		using RenderCommandFn = RenderCommandQueue::RenderCommandFn;

		// Commands
		static void Clear();
		static void Clear(float r, float g, float b, float a = 1.0f);
		static void SetClearColor(float r, float g, float b, float a);

		static void ClearMagenta();

		static void Init();

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader,
			const Ref<VertexArray>& vertexArray,
			rtm::matrix4x4f_argn transform = rtm::matrix_identity());

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		static void* Submit(RenderCommandFn fn, unsigned int size)
		{
			return s_Instance->m_CommandQueue.Allocate(fn, size);
		}

		void WaitAndRender();
		static Renderer& Get() { return *s_Instance; }

	private:
		struct SceneData
		{
			rtm::matrix4x4f ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;

		static Renderer* s_Instance;
		RenderCommandQueue m_CommandQueue;
	};
}

#define HEP_RENDER_PASTE2(a, b) a ## b
#define HEP_RENDER_PASTE(a, b) HEP_RENDER_PASTE2(a, b)
#define HEP_RENDER_UNIQUE(x) HEP_RENDER_PASTE(x, __LINE__)

#define HEP_RENDER(code) \
	struct HEP_RENDER_UNIQUE(HEPRenderCommand) \
	{\
		static void Execute(void*)\
		{\
			code\
		}\
	};\
	{\
		auto mem = RenderCommandQueue::Submit(sizeof(HEP_RENDER_UNIQUE(HEPRenderCommand)), HEP_RENDER_UNIQUE(HEPRenderCommand)::Execute);\
		new (mem) HEP_RENDER_UNIQUE(HEPRenderCommand)();\
	}

#define HEP_RENDER_1(arg0, code) \
	do {\
    struct HEP_RENDER_UNIQUE(HEPRenderCommand) \
    {\
		HEP_RENDER_UNIQUE(HEPRenderCommand)(::std::remove_cvref_t<decltype(arg0)> arg0) \
		: arg0(arg0) {}\
		\
        static void Execute(void* self)\
        {\
			auto& arg0 = ((HEP_RENDER_UNIQUE(HEPRenderCommand)*)self)->arg0;\
            code\
        }\
		\
		::std::remove_cvref_t<decltype(arg0)> arg0;\
    };\
	{\
		auto mem = ::Hep::Renderer::Submit(HEP_RENDER_UNIQUE(HEPRenderCommand)::Execute, sizeof(HEP_RENDER_UNIQUE(HEPRenderCommand)));\
		new (mem) HEP_RENDER_UNIQUE(HEPRenderCommand)(arg0);\
	} } while(0)

#define HEP_RENDER_2(arg0, arg1, code) \
    struct HEP_RENDER_UNIQUE(HEPRenderCommand) \
    {\
		HEP_RENDER_UNIQUE(HEPRenderCommand)(::std::remove_cvref_t<decltype(arg0)> arg0,\
											::std::remove_cvref_t<decltype(arg1)> arg1) \
		: arg0(arg0), arg1(arg1) {}\
		\
        static void Execute(void* self)\
        {\
			auto& arg0 = ((HEP_RENDER_UNIQUE(HEPRenderCommand)*)self)->arg0;\
			auto& arg1 = ((HEP_RENDER_UNIQUE(HEPRenderCommand)*)self)->arg1;\
            code\
        }\
		\
		::std::remove_cvref_t<decltype(arg0)> arg0;\
		::std::remove_cvref_t<decltype(arg1)> arg1;\
    };\
	{\
		auto mem = ::Hep::Renderer::Submit(HEP_RENDER_UNIQUE(HEPRenderCommand)::Execute, sizeof(HEP_RENDER_UNIQUE(HEPRenderCommand)));\
		new (mem) HEP_RENDER_UNIQUE(HEPRenderCommand)(arg0, arg1);\
	}
#define HEP_RENDER_3(arg0, arg1, arg2, code) \
    struct HEP_RENDER_UNIQUE(HEPRenderCommand) \
    {\
		HEP_RENDER_UNIQUE(HEPRenderCommand)(::std::remove_cvref_t<decltype(arg0)> arg0,\
											::std::remove_cvref_t<decltype(arg1)> arg1,\
											::std::remove_cvref_t<decltype(arg2)> arg2) \
		: arg0(arg0), arg1(arg1), arg2(arg2) {}\
		\
        static void Execute(void* self)\
        {\
			auto& arg0 = ((HEP_RENDER_UNIQUE(HEPRenderCommand)*)self)->arg0;\
			auto& arg1 = ((HEP_RENDER_UNIQUE(HEPRenderCommand)*)self)->arg1;\
			auto& arg2 = ((HEP_RENDER_UNIQUE(HEPRenderCommand)*)self)->arg2;\
            code\
        }\
		\
		::std::remove_cvref_t<decltype(arg0)> arg0;\
		::std::remove_cvref_t<decltype(arg1)> arg1;\
		::std::remove_cvref_t<decltype(arg2)> arg2;\
    };\
	{\
		auto mem = ::Hep::Renderer::Submit(HEP_RENDER_UNIQUE(HEPRenderCommand)::Execute, sizeof(HEP_RENDER_UNIQUE(HEPRenderCommand)));\
		new (mem) HEP_RENDER_UNIQUE(HEPRenderCommand)(arg0, arg1, arg2);\
	}
#define HEP_RENDER_4(arg0, arg1, arg2, arg3, code) \
    struct HEP_RENDER_UNIQUE(HEPRenderCommand) \
    {\
		HEP_RENDER_UNIQUE(HEPRenderCommand)(::std::remove_cvref_t<decltype(arg0)> arg0,\
											::std::remove_cvref_t<decltype(arg1)> arg1,\
											::std::remove_cvref_t<decltype(arg2)> arg2,\
											::std::remove_cvref_t<decltype(arg3)> arg3)\
		: arg0(arg0), arg1(arg1), arg2(arg2), arg3(arg3) {}\
		\
        static void Execute(void* self)\
        {\
			auto& arg0 = ((HEP_RENDER_UNIQUE(HEPRenderCommand)*)self)->arg0;\
			auto& arg1 = ((HEP_RENDER_UNIQUE(HEPRenderCommand)*)self)->arg1;\
			auto& arg2 = ((HEP_RENDER_UNIQUE(HEPRenderCommand)*)self)->arg2;\
			auto& arg3 = ((HEP_RENDER_UNIQUE(HEPRenderCommand)*)self)->arg3;\
            code\
        }\
		\
		::std::remove_cvref_t<decltype(arg0)> arg0;\
		::std::remove_cvref_t<decltype(arg1)> arg1;\
		::std::remove_cvref_t<decltype(arg2)> arg2;\
		::std::remove_cvref_t<decltype(arg3)> arg3;\
    };\
	{\
		auto mem = Renderer::Submit(HEP_RENDER_UNIQUE(HEPRenderCommand)::Execute, sizeof(HEP_RENDER_UNIQUE(HEPRenderCommand)));\
		new (mem) HEP_RENDER_UNIQUE(HEPRenderCommand)(arg0, arg1, arg2, arg3);\
	}
