#pragma once

#include <string>
#include <rtm/math.h>

#include "Hephaestus/Renderer/Shader.h"

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace Hep
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader() override;

		void Bind() const override;
		void Unbind() const override;

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, rtm::float2f& value);
		void UploadUniformFloat3(const std::string& name, rtm::float3f& value);
		void UploadUniformFloat4(const std::string& name, rtm::vector4f_arg1& value);
		void UploadUniformMat3(const std::string& name, rtm::matrix3x3f_arg1 matrix);
		void UploadUniformMat4(const std::string& name, rtm::matrix4x4f_arg1 matrix);

	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		GLint GetUniformLocation(const std::string& name) const;

	private:
		uint32_t m_RendererID;
		mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;
	};
}
