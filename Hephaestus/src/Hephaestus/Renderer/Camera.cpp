#include "heppch.h"
#include "Camera.h"

namespace Hep
{
	Camera::Camera(const glm::mat4& projectionMatrix)
		: m_ProjectionMatrix(projectionMatrix)
	{}
}
