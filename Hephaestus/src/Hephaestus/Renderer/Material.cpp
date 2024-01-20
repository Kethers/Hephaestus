#include "heppch.h"
#include "Material.h"

#include "Hephaestus/Platform/Vulkan/VulkanMaterial.h"
#include "Hephaestus/Platform/OpenGL/OpenGLMaterial.h"

#include "Hephaestus/Renderer/RendererAPI.h"

namespace Hep
{
	Ref<Material> Material::Create(const Ref<Shader>& shader, const std::string& name)
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None: return nullptr;
			case RendererAPIType::Vulkan: return Ref<VulkanMaterial>::Create(shader, name);
			case RendererAPIType::OpenGL: return Ref<OpenGLMaterial>::Create(shader, name);
		}
		HEP_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}
