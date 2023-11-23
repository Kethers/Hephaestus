#include "heppch.h"
#include "OrthographicCamera.h"

#include <rtm/rtm_ext.hpp>

namespace Hep
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(rtm::ext::ortho_off_center_lh(left, right, bottom, top, -1.0f, 1.0f)),
		  m_ViewMatrix(rtm::matrix_identity())
	{
		m_ViewProjectionMatrix = rtm::matrix_mul(m_ViewMatrix, m_ProjectionMatrix);
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		rtm::matrix4x4f transform = rtm::ext::transform_4x4(
			vector_load3(&m_Position),
			rtm::quat_from_axis_angle({ { 0.0f, 0.0f, 1.0f, 0.0f } }, rtm::scalar_deg_to_rad(m_Rotation)),
			rtm::vector_set(1.0f));

		m_ViewMatrix = rtm::matrix_inverse(transform);
		m_ViewProjectionMatrix = rtm::matrix_mul(m_ViewMatrix, m_ProjectionMatrix);
	}
}
