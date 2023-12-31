﻿using System;
using Hep;

namespace FPSExample
{
	public class FPSPlayer : Entity
	{
		public float WalkingSpeed = 10.0F;
		public float RunSpeed = 20.0F;
		public float JumpForce = 50.0F;
		public float MouseSensitivity = 10.0F;

		private bool m_Colliding = false;
		private float m_CurrentSpeed;

		private RigidBodyComponent m_RigidBody;
		private TransformComponent m_Transform;
		private TransformComponent m_CameraTransform;

		private Entity m_CameraEntity;

		private Vector2 m_LastMousePosition;

		private float m_CameraRotationX = 0.0F;
		private float m_RotationY = 0.0F;

		void OnCreate()
		{
			m_Transform = GetComponent<TransformComponent>();
			m_RigidBody = GetComponent<RigidBodyComponent>();

			m_CurrentSpeed = WalkingSpeed;

			AddCollisionBeginCallback((n) => { m_Colliding = true; });
			AddCollisionEndCallback((n) => { m_Colliding = false; });

			m_CameraEntity = FindEntityByTag("Camera");
			m_CameraTransform = m_CameraEntity.GetComponent<TransformComponent>();
			m_RotationY = m_Transform.Rotation.Y;

			m_LastMousePosition = Input.GetMousePosition();

			Input.SetCursorMode(CursorMode.Locked);
		}

		void OnUpdate(float ts)
		{
			if (Input.IsKeyPressed(KeyCode.Escape) && Input.GetCursorMode() == CursorMode.Locked)
				Input.SetCursorMode(CursorMode.Normal);

			if (Input.IsMouseButtonPressed(MouseButton.Left) && Input.GetCursorMode() == CursorMode.Normal)
				Input.SetCursorMode(CursorMode.Locked);

			m_CurrentSpeed = Input.IsKeyPressed(KeyCode.LeftShift) ? RunSpeed : WalkingSpeed;

			UpdateRotation(ts);
			UpdateMovement();
			UpdateCameraTransform();
		}

		private void UpdateRotation(float ts)
		{
			Vector2 currentMousePosition = Input.GetMousePosition();
			Vector2 delta = m_LastMousePosition - currentMousePosition;
			m_RotationY += delta.X * MouseSensitivity * ts;
			m_RigidBody.Rotate(new Vector3(0.0F, delta.X * MouseSensitivity, 0.0F) * ts);

			if (delta.Y != 0.0F)
			{
				m_CameraRotationX += delta.Y * MouseSensitivity * ts;
				m_CameraRotationX = Mathf.Clamp(m_CameraRotationX, -80.0F, 80.0F);
			}

			m_LastMousePosition = currentMousePosition;
		}

		Collider[] colliders = new Collider[10];

		private void UpdateMovement()
		{
			RaycastHit hitInfo;
			if (Input.IsKeyPressed(KeyCode.H) &&
				Physics.Raycast(m_CameraTransform.Transform.Translation + (m_CameraTransform.Forward * 5.0F), m_CameraTransform.Forward,
					20.0F, out hitInfo))
			{
				FindEntityByID(hitInfo.EntityID).GetComponent<MeshComponent>().Mesh.GetMaterial(0)
					.Set("u_AlbedoColor", new Vector3(1.0f, 0.0f, 0.0f));
			}

			if (Input.IsKeyPressed(KeyCode.L))
			{
				// NOTE: The NonAlloc version of Overlap functions should be used when possible since it doesn't allocate a new array
				//			whenever you call it. The normal versions allocates a brand new array every time.

				int numColliders = Physics.OverlapBoxNonAlloc(m_Transform.Transform.Translation, new Vector3(1.0F), colliders);

				// When using NonAlloc it's not safe to use a foreach loop since some of the colliders may not exist
				for (int i = 0; i < numColliders; i++)
				{
					Console.WriteLine(colliders[i]);
				}

				/*Collider[] colliders = Physics.OverlapBox(m_Transform.Transform.Translation, new Vector3(1.0f));
				Console.WriteLine(colliders.Length);

				foreach (Collider c in colliders)
				{
					Console.WriteLine("EntityID: {0}", c.EntityID);
					Console.WriteLine("IsTrigger: {0}", c.IsTrigger);
					Console.WriteLine("IsBox: {0}", c is BoxCollider);
					Console.WriteLine("IsSphere: {0}", c is SphereCollider);
					Console.WriteLine("IsCapsule: {0}", c is CapsuleCollider);
					Console.WriteLine("IsMesh: {0}", c is MeshCollider);
				}*/
			}

			if (Input.IsKeyPressed(KeyCode.W))
				m_RigidBody.AddForce(m_CameraTransform.Forward * m_CurrentSpeed);
			else if (Input.IsKeyPressed(KeyCode.S))
				m_RigidBody.AddForce(m_CameraTransform.Forward * -m_CurrentSpeed);

			if (Input.IsKeyPressed(KeyCode.A))
				m_RigidBody.AddForce(m_CameraTransform.Right * -m_CurrentSpeed);
			else if (Input.IsKeyPressed(KeyCode.D))
				m_RigidBody.AddForce(m_CameraTransform.Right * m_CurrentSpeed);

			if (Input.IsKeyPressed(KeyCode.Space) && m_Colliding)
				m_RigidBody.AddForce(Vector3.Up * JumpForce);
		}

		private void UpdateCameraTransform()
		{
			// TODO: This workflow needs to be improved. (Will be fixed by object parenting)
			Matrix4 cameraTransform = m_CameraTransform.Transform;
			Vector3 cameraTranslation = cameraTransform.Translation;
			Vector3 translation = m_Transform.Transform.Translation;
			cameraTranslation.XZ = translation.XZ;
			cameraTranslation.Y = translation.Y + 1.5F;
			cameraTransform.Translation = cameraTranslation;
			m_CameraTransform.Transform = cameraTransform;

			m_CameraTransform.Rotation = new Vector3(m_CameraRotationX, m_RotationY, 0.0F);
		}
	}
}