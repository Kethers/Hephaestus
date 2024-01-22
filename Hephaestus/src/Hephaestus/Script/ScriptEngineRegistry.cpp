#include "heppch.h"
#include "ScriptEngineRegistry.h"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Hephaestus/Scene/Entity.h"
#include "ScriptWrappers.h"

namespace Hep
{
	std::unordered_map<MonoType*, std::function<bool(Entity&)>> s_HasComponentFuncs;
	std::unordered_map<MonoType*, std::function<void(Entity&)>> s_CreateComponentFuncs;

	extern MonoImage* s_CoreAssemblyImage;

#define Component_RegisterType(Type) \
	{\
		MonoType* type = mono_reflection_type_from_name(const_cast<char*>("Hep." #Type), s_CoreAssemblyImage);\
		if (type) {\
			uint32_t id = mono_type_get_type(type);\
			s_HasComponentFuncs[type] = [](Entity& entity) { return entity.HasComponent<Type>(); };\
			s_CreateComponentFuncs[type] = [](Entity& entity) { entity.AddComponent<Type>(); };\
		} else {\
			HEP_CORE_ERROR("No C# component class found for " #Type "!");\
		}\
	}

	static void InitComponentTypes()
	{
		Component_RegisterType(TagComponent);
		Component_RegisterType(TransformComponent);
		Component_RegisterType(MeshComponent);
		Component_RegisterType(ScriptComponent);
		Component_RegisterType(CameraComponent);
		Component_RegisterType(SpriteRendererComponent);
		Component_RegisterType(RigidBody2DComponent);
		Component_RegisterType(BoxCollider2DComponent);
		Component_RegisterType(RigidBodyComponent);
		Component_RegisterType(BoxColliderComponent);
		Component_RegisterType(SphereColliderComponent);
	}

	void ScriptEngineRegistry::RegisterAll()
	{
		InitComponentTypes();

		mono_add_internal_call("Hep.Noise::PerlinNoise_Native", Hep::Script::Hep_Noise_PerlinNoise);

		mono_add_internal_call("Hep.Physics::Raycast_Native", Hep::Script::Hep_Physics_Raycast);
		mono_add_internal_call("Hep.Physics::OverlapBox_Native", Hep::Script::Hep_Physics_OverlapBox);
		mono_add_internal_call("Hep.Physics::OverlapCapsule_Native", Hep::Script::Hep_Physics_OverlapCapsule);
		mono_add_internal_call("Hep.Physics::OverlapSphere_Native", Hep::Script::Hep_Physics_OverlapSphere);
		mono_add_internal_call("Hep.Physics::OverlapBoxNonAlloc_Native", Hep::Script::Hep_Physics_OverlapBoxNonAlloc);
		mono_add_internal_call("Hep.Physics::OverlapCapsuleNonAlloc_Native", Hep::Script::Hep_Physics_OverlapCapsuleNonAlloc);
		mono_add_internal_call("Hep.Physics::OverlapSphereNonAlloc_Native", Hep::Script::Hep_Physics_OverlapSphereNonAlloc);

		mono_add_internal_call("Hep.Entity::CreateComponent_Native", Hep::Script::Hep_Entity_CreateComponent);
		mono_add_internal_call("Hep.Entity::HasComponent_Native", Hep::Script::Hep_Entity_HasComponent);
		mono_add_internal_call("Hep.Entity::FindEntityByTag_Native", Hep::Script::Hep_Entity_FindEntityByTag);

		mono_add_internal_call("Hep.TransformComponent::GetTransform_Native", Hep::Script::Hep_TransformComponent_GetTransform);
		mono_add_internal_call("Hep.TransformComponent::SetTransform_Native", Hep::Script::Hep_TransformComponent_SetTransform);
		mono_add_internal_call("Hep.TransformComponent::GetTranslation_Native", Hep::Script::Hep_TransformComponent_GetTranslation);
		mono_add_internal_call("Hep.TransformComponent::SetTranslation_Native", Hep::Script::Hep_TransformComponent_SetTranslation);
		mono_add_internal_call("Hep.TransformComponent::GetRotation_Native", Hep::Script::Hep_TransformComponent_GetRotation);
		mono_add_internal_call("Hep.TransformComponent::SetRotation_Native", Hep::Script::Hep_TransformComponent_SetRotation);
		mono_add_internal_call("Hep.TransformComponent::GetScale_Native", Hep::Script::Hep_TransformComponent_GetScale);
		mono_add_internal_call("Hep.TransformComponent::SetScale_Native", Hep::Script::Hep_TransformComponent_SetScale);
		mono_add_internal_call("Hep.TransformComponent::GetWorldTranslation_Native",
			Hep::Script::Hep_TransformComponent_GetWorldTranslation);

		mono_add_internal_call("Hep.MeshComponent::GetMesh_Native", Hep::Script::Hep_MeshComponent_GetMesh);
		mono_add_internal_call("Hep.MeshComponent::SetMesh_Native", Hep::Script::Hep_MeshComponent_SetMesh);

		mono_add_internal_call("Hep.RigidBody2DComponent::ApplyLinearImpulse_Native",
			Hep::Script::Hep_RigidBody2DComponent_ApplyLinearImpulse);
		mono_add_internal_call("Hep.RigidBody2DComponent::GetLinearVelocity_Native",
			Hep::Script::Hep_RigidBody2DComponent_GetLinearVelocity);
		mono_add_internal_call("Hep.RigidBody2DComponent::SetLinearVelocity_Native",
			Hep::Script::Hep_RigidBody2DComponent_SetLinearVelocity);

		mono_add_internal_call("Hep.RigidBodyComponent::GetBodyType_Native", Hep::Script::Hep_RigidBodyComponent_GetBodyType);
		mono_add_internal_call("Hep.RigidBodyComponent::AddForce_Native", Hep::Script::Hep_RigidBodyComponent_AddForce);
		mono_add_internal_call("Hep.RigidBodyComponent::AddTorque_Native", Hep::Script::Hep_RigidBodyComponent_AddTorque);
		mono_add_internal_call("Hep.RigidBodyComponent::GetLinearVelocity_Native", Hep::Script::Hep_RigidBodyComponent_GetLinearVelocity);
		mono_add_internal_call("Hep.RigidBodyComponent::SetLinearVelocity_Native", Hep::Script::Hep_RigidBodyComponent_SetLinearVelocity);
		mono_add_internal_call("Hep.RigidBodyComponent::GetAngularVelocity_Native", Hep::Script::Hep_RigidBodyComponent_GetAngularVelocity);
		mono_add_internal_call("Hep.RigidBodyComponent::SetAngularVelocity_Native", Hep::Script::Hep_RigidBodyComponent_SetAngularVelocity);
		mono_add_internal_call("Hep.RigidBodyComponent::Rotate_Native", Hep::Script::Hep_RigidBodyComponent_Rotate);
		mono_add_internal_call("Hep.RigidBodyComponent::GetLayer_Native", Hep::Script::Hep_RigidBodyComponent_GetLayer);
		mono_add_internal_call("Hep.RigidBodyComponent::GetMass_Native", Hep::Script::Hep_RigidBodyComponent_GetMass);
		mono_add_internal_call("Hep.RigidBodyComponent::SetMass_Native", Hep::Script::Hep_RigidBodyComponent_SetMass);

		mono_add_internal_call("Hep.Input::IsKeyPressed_Native", Hep::Script::Hep_Input_IsKeyPressed);
		mono_add_internal_call("Hep.Input::IsMouseButtonPressed_Native", Hep::Script::Hep_Input_IsMouseButtonPressed);
		mono_add_internal_call("Hep.Input::GetMousePosition_Native", Hep::Script::Hep_Input_GetMousePosition);
		mono_add_internal_call("Hep.Input::SetCursorMode_Native", Hep::Script::Hep_Input_SetCursorMode);
		mono_add_internal_call("Hep.Input::GetCursorMode_Native", Hep::Script::Hep_Input_GetCursorMode);

		mono_add_internal_call("Hep.Texture2D::Constructor_Native", Hep::Script::Hep_Texture2D_Constructor);
		mono_add_internal_call("Hep.Texture2D::Destructor_Native", Hep::Script::Hep_Texture2D_Destructor);
		mono_add_internal_call("Hep.Texture2D::SetData_Native", Hep::Script::Hep_Texture2D_SetData);

		mono_add_internal_call("Hep.Material::Destructor_Native", Hep::Script::Hep_Material_Destructor);
		mono_add_internal_call("Hep.Material::SetFloat_Native", Hep::Script::Hep_Material_SetFloat);
		mono_add_internal_call("Hep.Material::SetTexture_Native", Hep::Script::Hep_Material_SetTexture);

		mono_add_internal_call("Hep.MaterialInstance::Destructor_Native", Hep::Script::Hep_MaterialInstance_Destructor);
		mono_add_internal_call("Hep.MaterialInstance::SetFloat_Native", Hep::Script::Hep_MaterialInstance_SetFloat);
		mono_add_internal_call("Hep.MaterialInstance::SetVector3_Native", Hep::Script::Hep_MaterialInstance_SetVector3);
		mono_add_internal_call("Hep.MaterialInstance::SetVector4_Native", Hep::Script::Hep_MaterialInstance_SetVector4);
		mono_add_internal_call("Hep.MaterialInstance::SetTexture_Native", Hep::Script::Hep_MaterialInstance_SetTexture);

		mono_add_internal_call("Hep.Mesh::Constructor_Native", Hep::Script::Hep_Mesh_Constructor);
		mono_add_internal_call("Hep.Mesh::Destructor_Native", Hep::Script::Hep_Mesh_Destructor);
		mono_add_internal_call("Hep.Mesh::GetMaterial_Native", Hep::Script::Hep_Mesh_GetMaterial);
		mono_add_internal_call("Hep.Mesh::GetMaterialByIndex_Native", Hep::Script::Hep_Mesh_GetMaterialByIndex);
		mono_add_internal_call("Hep.Mesh::GetMaterialCount_Native", Hep::Script::Hep_Mesh_GetMaterialCount);

		mono_add_internal_call("Hep.MeshFactory::CreatePlane_Native", Hep::Script::Hep_MeshFactory_CreatePlane);
	}
}
