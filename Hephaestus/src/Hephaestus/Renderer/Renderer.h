#pragma once

#include "RenderCommandQueue.h"
#include "RendererAPI.h"
#include "RenderPass.h"

#include "Mesh.h"

namespace Hep
{
	class ShaderLibrary;

	// TODO: Maybe this should be renamed to RendererAPI? Because we want an actual renderer vs API calls...
	class Renderer
	{
	public:
		typedef void (*RenderCommandFn)(void*);

		// Commands
		static void Clear();
		static void Clear(float r, float g, float b, float a = 1.0f);
		static void SetClearColor(float r, float g, float b, float a);

		static void DrawIndexed(uint32_t count, bool depthTest = true);

		static void ClearMagenta();

		static void Init();

		static const Scope<ShaderLibrary>& GetShaderLibrary() { return Get().m_ShaderLibrary; }

		static void* Submit(RenderCommandFn fn, unsigned int size)
		{
			return s_Instance->m_CommandQueue.Allocate(fn, size);
		}

		void WaitAndRender();

		static Renderer& Get() { return *s_Instance; }

		// ~Actual~ Renderer here... TODO: remove confusion later
		static void BeginRenderPass(const Ref<RenderPass>& renderPass) { s_Instance->IBeginRenderPass(renderPass); }
		static void EndRenderPass() { s_Instance->IEndRenderPass(); }

		static void SubmitMesh(const Ref<Mesh>& mesh) { s_Instance->SubmitMeshI(mesh); }

	private:
		void IBeginRenderPass(const Ref<RenderPass>& renderPass);
		void IEndRenderPass();

		void SubmitMeshI(const Ref<Mesh>& mesh);

	private:
		static Renderer* s_Instance;

	private:
		Ref<RenderPass> m_ActiveRenderPass;
		RenderCommandQueue m_CommandQueue;
		Scope<ShaderLibrary> m_ShaderLibrary;
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
		auto mem = ::Hep::Renderer::Submit(HEP_RENDER_UNIQUE(HEPRenderCommand)::Execute, sizeof(HEP_RENDER_UNIQUE(HEPRenderCommand)));\
		new (mem) HEP_RENDER_UNIQUE(HEPRenderCommand)();\
	}

#define HEP_RENDER_1(arg0, code) \
	do {\
    struct HEP_RENDER_UNIQUE(HEPRenderCommand) \
    {\
		HEP_RENDER_UNIQUE(HEPRenderCommand)(::std::remove_cvref_t<decltype(arg0)> arg0) \
		: arg0(arg0) {}\
		\
        static void Execute(void* argBuffer)\
        {\
			auto& arg0 = ((HEP_RENDER_UNIQUE(HEPRenderCommand)*)argBuffer)->arg0;\
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
        static void Execute(void* argBuffer)\
        {\
			auto& arg0 = ((HEP_RENDER_UNIQUE(HEPRenderCommand)*)argBuffer)->arg0;\
			auto& arg1 = ((HEP_RENDER_UNIQUE(HEPRenderCommand)*)argBuffer)->arg1;\
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
        static void Execute(void* argBuffer)\
        {\
			auto& arg0 = ((HEP_RENDER_UNIQUE(HEPRenderCommand)*)argBuffer)->arg0;\
			auto& arg1 = ((HEP_RENDER_UNIQUE(HEPRenderCommand)*)argBuffer)->arg1;\
			auto& arg2 = ((HEP_RENDER_UNIQUE(HEPRenderCommand)*)argBuffer)->arg2;\
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
        static void Execute(void* argBuffer)\
        {\
			auto& arg0 = ((HEP_RENDER_UNIQUE(HEPRenderCommand)*)argBuffer)->arg0;\
			auto& arg1 = ((HEP_RENDER_UNIQUE(HEPRenderCommand)*)argBuffer)->arg1;\
			auto& arg2 = ((HEP_RENDER_UNIQUE(HEPRenderCommand)*)argBuffer)->arg2;\
			auto& arg3 = ((HEP_RENDER_UNIQUE(HEPRenderCommand)*)argBuffer)->arg3;\
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

#define HEP_RENDER_S(code) auto self = this;\
HEP_RENDER_1(self, code)

#define HEP_RENDER_S1(arg0, code) auto self = this;\
HEP_RENDER_2(self, arg0, code)

#define HEP_RENDER_S2(arg0, arg1, code) auto self = this;\
HEP_RENDER_3(self, arg0, arg1, code)

#define HEP_RENDER_S3(arg0, arg1, arg2, code) auto self = this;\
HEP_RENDER_4(self, arg0, arg1, arg2, code)
