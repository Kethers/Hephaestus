#pragma once

#include <glm/glm.hpp>

namespace Hep
{
	class Mat4
	{
	public:
		// static glm::mat4 FromAssimpMat4(const aiMatrix4x4& matrix);
	};

	std::tuple<glm::vec3, glm::quat, glm::vec3> GetTransformDecomposition(const glm::mat4& transform);
}
