#pragma once

#include <string>
#include <rtm/math.h>

namespace Hep
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformFloat4(const std::string& name, rtm::vector4f_arg1& values);
		void UploadUniformMat4(const std::string& name, rtm::matrix4x4f_arg1 matrix);

	private:
		uint32_t m_RendererID;
	};
}
