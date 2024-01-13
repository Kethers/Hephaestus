﻿#include "heppch.h"
#include "ScriptWrappers.h"

#include "Hephaestus/Core/Math/Noise.h"
#include "Hephaestus/Core/Math/Mat4.h"

#include "Hephaestus/Scene/Scene.h"
#include "Hephaestus/Scene/Entity.h"
#include "Hephaestus/Physics/PhysicsUtil.h"
#include "Hephaestus/Physics/PXPhysicsWrappers.h"
#include "Hephaestus/Physics/PhysicsActor.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/common.hpp>

#include <mono/jit/jit.h>

#include <box2d/box2d.h>

#include <PhysX/PxPhysicsAPI.h>

namespace Hep
{
	extern std::unordered_map<MonoType*, std::function<bool(Entity&)>> s_HasComponentFuncs;
	extern std::unordered_map<MonoType*, std::function<void(Entity&)>> s_CreateComponentFuncs;
}

namespace Hep::Script
{
	////////////////////////////////////////////////////////////////
	// Math ////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////

	float Hep_Noise_PerlinNoise(float x, float y)
	{
		return Noise::PerlinNoise(x, y);
	}

	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	// Input ///////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////

	bool Hep_Input_IsKeyPressed(KeyCode key)
	{
		return Input::IsKeyPressed(key);
	}

	bool Hep_Input_IsMouseButtonPressed(MouseButton button)
	{
		return Input::IsMouseButtonPressed(button);
	}

	void Hep_Input_GetMousePosition(glm::vec2* outPosition)
	{
		auto [x, y] = Input::GetMousePosition();
		*outPosition = { x, y };
	}

	void Hep_Input_SetCursorMode(CursorMode mode)
	{
		Input::SetCursorMode(mode);
	}

	CursorMode Hep_Input_GetCursorMode()
	{
		return Input::GetCursorMode();
	}

	bool Hep_Physics_Raycast(glm::vec3* origin, glm::vec3* direction, float maxDistance, RaycastHit* hit)
	{
		return PXPhysicsWrappers::Raycast(*origin, *direction, maxDistance, hit);
	}

	// Helper function for the Overlap functions below
	static void AddCollidersToArray(MonoArray* array, const std::array<physx::PxOverlapHit, OVERLAP_MAX_COLLIDERS>& hits, uint32_t count,
		uint32_t arrayLength)
	{
		uint32_t arrayIndex = 0;
		for (uint32_t i = 0; i < count; i++)
		{
			Entity& entity = *(Entity*)hits[i].actor->userData;

			if (entity.HasComponent<BoxColliderComponent>() && arrayIndex < arrayLength)
			{
				auto& boxCollider = entity.GetComponent<BoxColliderComponent>();

				UUID uuid = entity.GetUUID();
				void* data[] = {
					&uuid,
					&boxCollider.IsTrigger,
					&boxCollider.Size,
					&boxCollider.Offset
				};

				MonoObject* obj = ScriptEngine::Construct("Hep.BoxCollider:.ctor(ulong,bool,Vector3,Vector3)", true, data);
				mono_array_set(array, MonoObject*, arrayIndex++, obj);
			}

			if (entity.HasComponent<SphereColliderComponent>() && arrayIndex < arrayLength)
			{
				auto& sphereCollider = entity.GetComponent<SphereColliderComponent>();

				UUID uuid = entity.GetUUID();
				void* data[] = {
					&uuid,
					&sphereCollider.IsTrigger,
					&sphereCollider.Radius
				};

				MonoObject* obj = ScriptEngine::Construct("Hep.SphereCollider:.ctor(ulong,bool,single)", true, data);
				mono_array_set(array, MonoObject*, arrayIndex++, obj);
			}

			if (entity.HasComponent<CapsuleColliderComponent>() && arrayIndex < arrayLength)
			{
				auto& capsuleCollider = entity.GetComponent<CapsuleColliderComponent>();

				UUID uuid = entity.GetUUID();
				void* data[] = {
					&uuid,
					&capsuleCollider.IsTrigger,
					&capsuleCollider.Radius,
					&capsuleCollider.Height
				};

				MonoObject* obj = ScriptEngine::Construct("Hep.CapsuleCollider:.ctor(ulong,bool,single,single)", true, data);
				mono_array_set(array, MonoObject*, arrayIndex++, obj);
			}

			if (entity.HasComponent<MeshColliderComponent>() && arrayIndex < arrayLength)
			{
				auto& meshCollider = entity.GetComponent<MeshColliderComponent>();

				Ref<Mesh>* mesh = new Ref<Mesh>(meshCollider.CollisionMesh);
				UUID uuid = entity.GetUUID();
				void* data[] = {
					&uuid,
					&meshCollider.IsTrigger,
					&mesh
				};

				MonoObject* obj = ScriptEngine::Construct("Hep.MeshCollider:.ctor(ulong,bool,intptr)", true, data);
				mono_array_set(array, MonoObject*, arrayIndex++, obj);
			}
		}
	}

	static std::array<physx::PxOverlapHit, OVERLAP_MAX_COLLIDERS> s_OverlapBuffer;

	MonoArray* Hep_Physics_OverlapBox(glm::vec3* origin, glm::vec3* halfSize)
	{
		MonoArray* outColliders = nullptr;
		memset(s_OverlapBuffer.data(), 0, OVERLAP_MAX_COLLIDERS * sizeof(physx::PxOverlapHit));

		uint32_t count;
		if (PXPhysicsWrappers::OverlapBox(*origin, *halfSize, s_OverlapBuffer, &count))
		{
			outColliders = mono_array_new(mono_domain_get(), ScriptEngine::GetCoreClass("Hep.Collider"), count);
			AddCollidersToArray(outColliders, s_OverlapBuffer, count, count);
		}

		return outColliders;
	}

	MonoArray* Hep_Physics_OverlapCapsule(glm::vec3* origin, float radius, float halfHeight)
	{
		MonoArray* outColliders = nullptr;
		memset(s_OverlapBuffer.data(), 0, OVERLAP_MAX_COLLIDERS * sizeof(physx::PxOverlapHit));

		uint32_t count;
		if (PXPhysicsWrappers::OverlapCapsule(*origin, radius, halfHeight, s_OverlapBuffer, &count))
		{
			outColliders = mono_array_new(mono_domain_get(), ScriptEngine::GetCoreClass("Hep.Collider"), count);
			AddCollidersToArray(outColliders, s_OverlapBuffer, count, count);
		}

		return outColliders;
	}

	MonoArray* Hep_Physics_OverlapSphere(glm::vec3* origin, float radius)
	{
		MonoArray* outColliders = nullptr;
		memset(s_OverlapBuffer.data(), 0, OVERLAP_MAX_COLLIDERS * sizeof(physx::PxOverlapHit));

		uint32_t count;
		if (PXPhysicsWrappers::OverlapSphere(*origin, radius, s_OverlapBuffer, &count))
		{
			outColliders = mono_array_new(mono_domain_get(), ScriptEngine::GetCoreClass("Hep.Collider"), count);
			AddCollidersToArray(outColliders, s_OverlapBuffer, count, count);
		}

		return outColliders;
	}

	int32_t Hep_Physics_OverlapBoxNonAlloc(glm::vec3* origin, glm::vec3* halfSize, MonoArray* outColliders)
	{
		memset(s_OverlapBuffer.data(), 0, OVERLAP_MAX_COLLIDERS * sizeof(physx::PxOverlapHit));

		uint64_t arrayLength = mono_array_length(outColliders);

		uint32_t count;
		if (PXPhysicsWrappers::OverlapBox(*origin, *halfSize, s_OverlapBuffer, &count))
		{
			if (count > arrayLength)
				count = arrayLength;

			AddCollidersToArray(outColliders, s_OverlapBuffer, count, arrayLength);
		}

		return count;
	}

	int32_t Hep_Physics_OverlapCapsuleNonAlloc(glm::vec3* origin, float radius, float halfHeight, MonoArray* outColliders)
	{
		memset(s_OverlapBuffer.data(), 0, OVERLAP_MAX_COLLIDERS * sizeof(physx::PxOverlapHit));

		uint64_t arrayLength = mono_array_length(outColliders);
		uint32_t count;
		if (PXPhysicsWrappers::OverlapCapsule(*origin, radius, halfHeight, s_OverlapBuffer, &count))
		{
			if (count > arrayLength)
				count = arrayLength;

			AddCollidersToArray(outColliders, s_OverlapBuffer, count, arrayLength);
		}

		return count;
	}

	int32_t Hep_Physics_OverlapSphereNonAlloc(glm::vec3* origin, float radius, MonoArray* outColliders)
	{
		memset(s_OverlapBuffer.data(), 0, OVERLAP_MAX_COLLIDERS * sizeof(physx::PxOverlapHit));

		uint64_t arrayLength = mono_array_length(outColliders);

		uint32_t count;
		if (PXPhysicsWrappers::OverlapSphere(*origin, radius, s_OverlapBuffer, &count))
		{
			if (count > arrayLength)
				count = arrayLength;

			AddCollidersToArray(outColliders, s_OverlapBuffer, count, arrayLength);
		}

		return count;
	}

	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	// Entity //////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////

	void Hep_Entity_CreateComponent(uint64_t entityID, void* type)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		MonoType* monoType = mono_reflection_type_get_type((MonoReflectionType*)type);
		s_CreateComponentFuncs[monoType](entity);
	}

	bool Hep_Entity_HasComponent(uint64_t entityID, void* type)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		MonoType* monoType = mono_reflection_type_get_type((MonoReflectionType*)type);
		bool result = s_HasComponentFuncs[monoType](entity);
		return result;
	}

	uint64_t Hep_Entity_FindEntityByTag(MonoString* tag)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");

		Entity entity = scene->FindEntityByTag(mono_string_to_utf8(tag));
		if (entity)
			return entity.GetComponent<IDComponent>().ID;

		return 0;
	}

	void Hep_TransformComponent_GetTransform(uint64_t entityID, TransformComponent* outTransform)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		*outTransform = entity.GetComponent<TransformComponent>();
	}

	void Hep_TransformComponent_SetTransform(uint64_t entityID, TransformComponent* inTransform)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		entity.GetComponent<TransformComponent>() = *inTransform;
	}

	void Hep_TransformComponent_GetTranslation(uint64_t entityID, glm::vec3* outTranslation)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		*outTranslation = entity.GetComponent<TransformComponent>().Translation;
	}

	void Hep_TransformComponent_SetTranslation(uint64_t entityID, glm::vec3* inTranslation)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		entity.GetComponent<TransformComponent>().Translation = *inTranslation;
	}

	void Hep_TransformComponent_GetRotation(uint64_t entityID, glm::vec3* outRotation)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		*outRotation = entity.GetComponent<TransformComponent>().Rotation;
	}

	void Hep_TransformComponent_SetRotation(uint64_t entityID, glm::vec3* inRotation)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		entity.GetComponent<TransformComponent>().Rotation = *inRotation;
	}

	void Hep_TransformComponent_GetScale(uint64_t entityID, glm::vec3* outScale)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		*outScale = entity.GetComponent<TransformComponent>().Scale;
	}

	void Hep_TransformComponent_SetScale(uint64_t entityID, glm::vec3* inScale)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		entity.GetComponent<TransformComponent>().Scale = *inScale;
	}

	void* Hep_MeshComponent_GetMesh(uint64_t entityID)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		auto& meshComponent = entity.GetComponent<MeshComponent>();
		return new Ref<Mesh>(meshComponent.Mesh);
	}

	void Hep_MeshComponent_SetMesh(uint64_t entityID, Ref<Mesh>* inMesh)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		auto& meshComponent = entity.GetComponent<MeshComponent>();
		meshComponent.Mesh = inMesh ? *inMesh : nullptr;
	}

	void Hep_RigidBody2DComponent_ApplyLinearImpulse(uint64_t entityID, glm::vec2* impulse, glm::vec2* offset, bool wake)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		HEP_CORE_ASSERT(entity.HasComponent<RigidBody2DComponent>());
		auto& component = entity.GetComponent<RigidBody2DComponent>();
		b2Body* body = (b2Body*)component.RuntimeBody;
		body->ApplyLinearImpulse(*(const b2Vec2*)impulse, body->GetWorldCenter() + *(const b2Vec2*)offset, wake);
	}

	void Hep_RigidBody2DComponent_GetLinearVelocity(uint64_t entityID, glm::vec2* outVelocity)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		HEP_CORE_ASSERT(entity.HasComponent<RigidBody2DComponent>());
		auto& component = entity.GetComponent<RigidBody2DComponent>();
		auto body = (b2Body*)component.RuntimeBody;
		const auto& velocity = body->GetLinearVelocity();
		HEP_CORE_ASSERT(outVelocity);
		*outVelocity = { velocity.x, velocity.y };
	}

	void Hep_RigidBody2DComponent_SetLinearVelocity(uint64_t entityID, glm::vec2* velocity)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		HEP_CORE_ASSERT(entity.HasComponent<RigidBody2DComponent>());
		auto& component = entity.GetComponent<RigidBody2DComponent>();
		b2Body* body = (b2Body*)component.RuntimeBody;
		HEP_CORE_ASSERT(velocity);
		body->SetLinearVelocity({ velocity->x, velocity->y });
	}

	RigidBodyComponent::Type Hep_RigidBodyComponent_GetBodyType(uint64_t entityID)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		HEP_CORE_ASSERT(entity.HasComponent<RigidBodyComponent>());
		auto& component = entity.GetComponent<RigidBodyComponent>();
		return component.BodyType;
	}

	void Hep_RigidBodyComponent_AddForce(uint64_t entityID, glm::vec3* force, ForceMode forceMode)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		HEP_CORE_ASSERT(entity.HasComponent<RigidBodyComponent>());
		auto& component = entity.GetComponent<RigidBodyComponent>();

		if (component.IsKinematic)
		{
			HEP_CORE_WARN("Cannot add a force to a kinematic actor! EntityID({0})", entityID);
			return;
		}

		Ref<PhysicsActor> actor = Physics::GetActorForEntity(entity);
		actor->AddForce(*force, forceMode);
	}

	void Hep_RigidBodyComponent_AddTorque(uint64_t entityID, glm::vec3* torque, ForceMode forceMode)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		HEP_CORE_ASSERT(entity.HasComponent<RigidBodyComponent>());
		auto& component = entity.GetComponent<RigidBodyComponent>();

		if (component.IsKinematic)
		{
			HEP_CORE_WARN("Cannot add a torque to a kinematic actor! EntityID({0})", entityID);
			return;
		}

		Ref<PhysicsActor> actor = Physics::GetActorForEntity(entity);
		actor->AddTorque(*torque, forceMode);
	}

	void Hep_RigidBodyComponent_GetLinearVelocity(uint64_t entityID, glm::vec3* outVelocity)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		HEP_CORE_ASSERT(entity.HasComponent<RigidBodyComponent>());
		auto& component = entity.GetComponent<RigidBodyComponent>();
		HEP_CORE_ASSERT(outVelocity);
		Ref<PhysicsActor> actor = Physics::GetActorForEntity(entity);
		*outVelocity = actor->GetLinearVelocity();
	}

	void Hep_RigidBodyComponent_SetLinearVelocity(uint64_t entityID, glm::vec3* velocity)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		HEP_CORE_ASSERT(entity.HasComponent<RigidBodyComponent>());

		auto& component = entity.GetComponent<RigidBodyComponent>();
		HEP_CORE_ASSERT(velocity);
		Ref<PhysicsActor> actor = Physics::GetActorForEntity(entity);
		actor->SetLinearVelocity(*velocity);
	}

	void Hep_RigidBodyComponent_GetAngularVelocity(uint64_t entityID, glm::vec3* outVelocity)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		HEP_CORE_ASSERT(entity.HasComponent<RigidBodyComponent>());
		auto& component = entity.GetComponent<RigidBodyComponent>();
		HEP_CORE_ASSERT(outVelocity);
		Ref<PhysicsActor> actor = Physics::GetActorForEntity(entity);
		*outVelocity = actor->GetAngularVelocity();
	}

	void Hep_RigidBodyComponent_SetAngularVelocity(uint64_t entityID, glm::vec3* velocity)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		HEP_CORE_ASSERT(entity.HasComponent<RigidBodyComponent>());
		auto& component = entity.GetComponent<RigidBodyComponent>();
		HEP_CORE_ASSERT(velocity);
		Ref<PhysicsActor> actor = Physics::GetActorForEntity(entity);
		actor->SetAngularVelocity(*velocity);
	}

	void Hep_RigidBodyComponent_Rotate(uint64_t entityID, glm::vec3* rotation)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		HEP_CORE_ASSERT(entity.HasComponent<RigidBodyComponent>());
		auto& component = entity.GetComponent<RigidBodyComponent>();
		HEP_CORE_ASSERT(rotation);
		Ref<PhysicsActor> actor = Physics::GetActorForEntity(entity);
		actor->Rotate(*rotation);
	}

	uint32_t Hep_RigidBodyComponent_GetLayer(uint64_t entityID)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		HEP_CORE_ASSERT(entity.HasComponent<RigidBodyComponent>());
		auto& component = entity.GetComponent<RigidBodyComponent>();
		return component.Layer;
	}

	float Hep_RigidBodyComponent_GetMass(uint64_t entityID)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		HEP_CORE_ASSERT(entity.HasComponent<RigidBodyComponent>());
		auto& component = entity.GetComponent<RigidBodyComponent>();
		Ref<PhysicsActor> actor = Physics::GetActorForEntity(entity);
		return actor->GetMass();
	}

	void Hep_RigidBodyComponent_SetMass(uint64_t entityID, float mass)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		HEP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		HEP_CORE_ASSERT(entityMap.contains(entityID), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		HEP_CORE_ASSERT(entity.HasComponent<RigidBodyComponent>());
		auto& component = entity.GetComponent<RigidBodyComponent>();
		Ref<PhysicsActor> actor = Physics::GetActorForEntity(entity);
		actor->SetMass(mass);
	}

	Ref<Mesh>* Hep_Mesh_Constructor(MonoString* filepath)
	{
		return new Ref<Mesh>(new Mesh(mono_string_to_utf8(filepath)));
	}

	void Hep_Mesh_Destructor(Ref<Mesh>* _this)
	{
		Ref<Mesh>* instance = (Ref<Mesh>*)_this;
		delete _this;
	}

	Ref<Material>* Hep_Mesh_GetMaterial(Ref<Mesh>* inMesh)
	{
		Ref<Mesh>& mesh = *(Ref<Mesh>*)inMesh;
		return new Ref<Material>(mesh->GetMaterial());
	}

	Ref<MaterialInstance>* Hep_Mesh_GetMaterialByIndex(Ref<Mesh>* inMesh, int index)
	{
		Ref<Mesh>& mesh = *(Ref<Mesh>*)inMesh;
		const auto& materials = mesh->GetMaterials();

		HEP_CORE_ASSERT(index < materials.size());
		return new Ref<MaterialInstance>(materials[index]);
	}

	int Hep_Mesh_GetMaterialCount(Ref<Mesh>* inMesh)
	{
		Ref<Mesh>& mesh = *(Ref<Mesh>*)inMesh;
		const auto& materials = mesh->GetMaterials();
		return materials.size();
	}

	void* Hep_Texture2D_Constructor(uint32_t width, uint32_t height)
	{
		auto result = Texture2D::Create(TextureFormat::RGBA, width, height);
		return new Ref<Texture2D>(result);
	}

	void Hep_Texture2D_Destructor(Ref<Texture2D>* _this)
	{
		delete _this;
	}

	void Hep_Texture2D_SetData(Ref<Texture2D>* _this, MonoArray* inData, int32_t count)
	{
		Ref<Texture2D>& instance = *_this;

		uint32_t dataSize = count * sizeof(glm::vec4) / 4;

		instance->Lock();
		Buffer buffer = instance->GetWriteableBuffer();
		HEP_CORE_ASSERT(dataSize <= buffer.Size);
		// Convert RGBA32F color to RGBA8
		uint8_t* pixels = (uint8_t*)buffer.Data;
		uint32_t index = 0;
		for (int i = 0; i < instance->GetWidth() * instance->GetHeight(); i++)
		{
			glm::vec4& value = mono_array_get(inData, glm::vec4, i);
			*pixels++ = (uint32_t)(value.x * 255.0f);
			*pixels++ = (uint32_t)(value.y * 255.0f);
			*pixels++ = (uint32_t)(value.z * 255.0f);
			*pixels++ = (uint32_t)(value.w * 255.0f);
		}

		instance->Unlock();
	}

	void Hep_Material_Destructor(Ref<Material>* _this)
	{
		delete _this;
	}

	void Hep_Material_SetFloat(Ref<Material>* _this, MonoString* uniform, float value)
	{
		Ref<Material>& instance = *(Ref<Material>*)_this;
		instance->Set(mono_string_to_utf8(uniform), value);
	}

	void Hep_Material_SetTexture(Ref<Material>* _this, MonoString* uniform, Ref<Texture2D>* texture)
	{
		Ref<Material>& instance = *(Ref<Material>*)_this;
		instance->Set(mono_string_to_utf8(uniform), *texture);
	}

	void Hep_MaterialInstance_Destructor(Ref<MaterialInstance>* _this)
	{
		delete _this;
	}

	void Hep_MaterialInstance_SetFloat(Ref<MaterialInstance>* _this, MonoString* uniform, float value)
	{
		Ref<MaterialInstance>& instance = *(Ref<MaterialInstance>*)_this;
		instance->Set(mono_string_to_utf8(uniform), value);
	}

	void Hep_MaterialInstance_SetVector3(Ref<MaterialInstance>* _this, MonoString* uniform, glm::vec3* value)
	{
		Ref<MaterialInstance>& instance = *(Ref<MaterialInstance>*)_this;
		instance->Set(mono_string_to_utf8(uniform), *value);
	}

	void Hep_MaterialInstance_SetVector4(Ref<MaterialInstance>* _this, MonoString* uniform, glm::vec4* value)
	{
		Ref<MaterialInstance>& instance = *(Ref<MaterialInstance>*)_this;
		instance->Set(mono_string_to_utf8(uniform), *value);
	}

	void Hep_MaterialInstance_SetTexture(Ref<MaterialInstance>* _this, MonoString* uniform, Ref<Texture2D>* texture)
	{
		Ref<MaterialInstance>& instance = *(Ref<MaterialInstance>*)_this;
		instance->Set(mono_string_to_utf8(uniform), *texture);
	}

	void* Hep_MeshFactory_CreatePlane(float width, float height)
	{
		// TODO: Implement properly with MeshFactory class!
		return new Ref<Mesh>(new Mesh("assets/models/Plane1m.obj"));
	}

	////////////////////////////////////////////////////////////////
}
