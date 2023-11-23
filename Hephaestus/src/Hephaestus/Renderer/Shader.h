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

		void UploadUniformMat4(const std::string& name, const rtm::matrix4x4f& matrix);

	private:
		uint32_t m_RendererID;
	};
}
