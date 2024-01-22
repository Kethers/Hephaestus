﻿#pragma once

#include "Hephaestus/Renderer/Material.h"

#include "Hephaestus/Platform/Vulkan/VulkanShader.h"

namespace Hep
{
	class VulkanMaterial : public Material
	{
	public:
		VulkanMaterial(const Ref<Shader>& shader, const std::string& name = "");
		~VulkanMaterial() override;

		void Invalidate() override;

		void Set(const std::string& name, float value) override;
		void Set(const std::string& name, int value) override;
		void Set(const std::string& name, uint32_t value) override;
		void Set(const std::string& name, bool value) override;
		void Set(const std::string& name, const glm::vec2& value) override;
		void Set(const std::string& name, const glm::vec3& value) override;
		void Set(const std::string& name, const glm::vec4& value) override;
		void Set(const std::string& name, const glm::mat3& value) override;
		void Set(const std::string& name, const glm::mat4& value) override;

		void Set(const std::string& name, const Ref<Texture2D>& texture) override;
		void Set(const std::string& name, const Ref<TextureCube>& texture) override;
		void Set(const std::string& name, const Ref<Image2D>& image) override;

		float& GetFloat(const std::string& name) override;
		int32_t& GetInt(const std::string& name) override;
		uint32_t& GetUInt(const std::string& name) override;
		bool& GetBool(const std::string& name) override;
		glm::vec2& GetVector2(const std::string& name) override;
		glm::vec3& GetVector3(const std::string& name) override;
		glm::vec4& GetVector4(const std::string& name) override;
		glm::mat3& GetMatrix3(const std::string& name) override;
		glm::mat4& GetMatrix4(const std::string& name) override;

		Ref<Texture2D> GetTexture2D(const std::string& name) override;
		Ref<TextureCube> GetTextureCube(const std::string& name) override;

		Ref<Texture2D> TryGetTexture2D(const std::string& name) override;
		Ref<TextureCube> TryGetTextureCube(const std::string& name) override;

		template <typename T>
		void Set(const std::string& name, const T& value)
		{
			auto decl = FindUniformDeclaration(name);
			HEP_CORE_ASSERT(decl, "Could not find uniform!");
			if (!decl)
				return;

			auto& buffer = m_UniformStorageBuffer;
			buffer.Write((byte*)&value, decl->GetSize(), decl->GetOffset());
		}

		template <typename T>
		T& Get(const std::string& name)
		{
			auto decl = FindUniformDeclaration(name);
			HEP_CORE_ASSERT(decl, "Could not find uniform with name 'x'");
			auto& buffer = m_UniformStorageBuffer;
			return buffer.Read<T>(decl->GetOffset());
		}

		template <typename T>
		Ref<T> GetResource(const std::string& name)
		{
			auto decl = FindResourceDeclaration(name);
			HEP_CORE_ASSERT(decl, "Could not find uniform with name 'x'");
			uint32_t slot = decl->GetRegister();
			HEP_CORE_ASSERT(slot < m_Textures.size(), "Texture slot is invalid!");
			return Ref<T>(m_Textures[slot]);
		}

		template <typename T>
		Ref<T> TryGetResource(const std::string& name)
		{
			auto decl = FindResourceDeclaration(name);
			if (!decl)
				return nullptr;

			uint32_t slot = decl->GetRegister();
			if (slot >= m_Textures.size())
				return nullptr;

			return Ref<T>(m_Textures[slot]);
		}

		uint32_t GetFlags() const override { return m_MaterialFlags; }
		bool GetFlag(MaterialFlag flag) const override { return (uint32_t)flag & m_MaterialFlags; }
		void SetFlag(MaterialFlag flag, bool value = true) override
		{
			if (value)
			{
				m_MaterialFlags |= (uint32_t)flag;
			}
			else
			{
				m_MaterialFlags &= ~(uint32_t)flag;
			}
		}

		Ref<Shader> GetShader() override { return m_Shader; }
		const std::string& GetName() const override { return m_Name; }

		Buffer GetUniformStorageBuffer() { return m_UniformStorageBuffer; }

		void UpdateForRendering();

		const VulkanShader::ShaderMaterialDescriptorSet& GetDescriptorSet() { return m_DescriptorSet; }

	private:
		void Init();
		void AllocateStorage();
		void OnShaderReloaded();

		void SetVulkanDescriptor(const std::string& name, const Ref<Texture2D>& texture);
		void SetVulkanDescriptor(const std::string& name, const Ref<TextureCube>& texture);
		void SetVulkanDescriptor(const std::string& name, const Ref<Image2D>& image);
		void SetVulkanDescriptor(const std::string& name, const VkDescriptorImageInfo& imageInfo);

		const ShaderUniform* FindUniformDeclaration(const std::string& name);
		const ShaderResourceDeclaration* FindResourceDeclaration(const std::string& name);

	private:
		Ref<Shader> m_Shader;
		std::string m_Name;

		enum class PendingDescriptorType
		{
			None = 0, Texture2D, TextureCube, Image2D
		};

		struct PendingDescriptor
		{
			PendingDescriptorType Type = PendingDescriptorType::None;
			VkWriteDescriptorSet WDS;
			VkDescriptorImageInfo ImageInfo{};
			Ref<Texture> Texture;
			Ref<Image> Image;
			VkDescriptorImageInfo SubmittedImageInfo{};
		};

		std::unordered_map<uint32_t, std::shared_ptr<PendingDescriptor>> m_ResidentDescriptors;
		std::vector<std::shared_ptr<PendingDescriptor>> m_PendingDescriptors; // TODO: weak ref

		uint32_t m_MaterialFlags = 0;

		Buffer m_UniformStorageBuffer;
		std::vector<Ref<Texture>> m_Textures; // TODO: Texture should only be stored as images
		std::vector<Ref<Image>> m_Images;

		std::unordered_map<uint32_t, uint64_t> m_ImageHashes;

		VulkanShader::ShaderMaterialDescriptorSet m_DescriptorSet;
		std::vector<VkWriteDescriptorSet> m_WriteDescriptors;

		std::unordered_map<std::string, VkDescriptorImageInfo> m_ImageInfos;
	};
}