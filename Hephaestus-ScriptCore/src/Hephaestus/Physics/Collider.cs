﻿using System;

namespace Hep
{
	public class Collider
	{
		public ulong EntityID { get; protected set; }
		public bool IsTrigger { get; protected set; }

		private Entity entity;
		private RigidBodyComponent _rigidBodyComponent;

		public Entity Entity => entity ?? (entity = new Entity(EntityID));

		public RigidBodyComponent RigidBody => _rigidBodyComponent ?? (_rigidBodyComponent = Entity.GetComponent<RigidBodyComponent>());

		public override string ToString()
		{
			string type = "Collider";

			switch (this)
			{
				case BoxCollider _:
					type = "BoxCollider";
					break;
				case SphereCollider _:
					type = "SphereCollider";
					break;
				case CapsuleCollider _:
					type = "CapsuleCollider";
					break;
				case MeshCollider _:
					type = "MeshCollider";
					break;
			}

			return "Collider(" + type + ", " + EntityID + ", " + IsTrigger + ")";
		}
	}

	public class BoxCollider : Collider
	{
		public Vector3 Size { get; protected set; }
		public Vector3 Offset { get; protected set; }

		internal BoxCollider(ulong entityID, bool isTrigger, Vector3 size, Vector3 offset)
		{
			EntityID = entityID;
			IsTrigger = isTrigger;
			Size = size;
			Offset = offset;
		}
	}

	public class SphereCollider : Collider
	{
		public float Radius { get; protected set; }

		internal SphereCollider(ulong entityID, bool isTrigger, float radius)
		{
			EntityID = entityID;
			IsTrigger = isTrigger;
			Radius = radius;
		}
	}

	public class CapsuleCollider : Collider
	{
		public float Radius { get; protected set; }
		public float Height { get; protected set; }

		internal CapsuleCollider(ulong entityID, bool isTrigger, float radius, float height)
		{
			EntityID = entityID;
			IsTrigger = isTrigger;
			Radius = radius;
			Height = height;
		}
	}

	public class MeshCollider : Collider
	{
		public Mesh Mesh { get; protected set; }

		internal MeshCollider(ulong entityID, bool isTrigger, IntPtr mesh)
		{
			EntityID = entityID;
			IsTrigger = isTrigger;
			Mesh = new Mesh(mesh);
		}
	}
}