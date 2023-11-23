#pragma once

#include <rtm/math.h>

namespace Hep
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		const rtm::float3f& GetPosition() const { return m_Position; }

		void SetPosition(const rtm::float3f& position)
		{
			m_Position = position;
			RecalculateViewMatrix();
		}

		float GetRotation() const { return m_Rotation; }

		void SetRotation(float rotation)
		{
			m_Rotation = rotation;
			RecalculateViewMatrix();
		}

		const rtm::matrix4x4f GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const rtm::matrix4x4f GetViewMatrix() const { return m_ViewMatrix; }
		const rtm::matrix4x4f GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();

	private:
		rtm::matrix4x4f m_ProjectionMatrix;
		rtm::matrix4x4f m_ViewMatrix;
		rtm::matrix4x4f m_ViewProjectionMatrix;

		rtm::float3f m_Position{};
		float m_Rotation = 0.0f;
	};
}
