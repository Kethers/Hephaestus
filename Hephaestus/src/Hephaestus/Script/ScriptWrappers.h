#pragma once

#include "Hephaestus/Script/ScriptEngine.h"
#include "Hephaestus/Core/Input.h"
#include "Hephaestus/Physics/Physics.h"

#include <glm/glm.hpp>

extern "C"
{
	typedef struct _MonoString MonoString;
	typedef struct _MonoArray MonoArray;
}

namespace Hep::Script
{
	// Math
	float Hep_Noise_PerlinNoise(float x, float y);

	// Input
	bool Hep_Input_IsKeyPressed(KeyCode key);
	bool Hep_Input_IsMouseButtonPressed(MouseButton button);
	void Hep_Input_GetMousePosition(glm::vec2* outPosition);
	void Hep_Input_SetCursorMode(CursorMode mode);
	CursorMode Hep_Input_GetCursorMode();

	// Physics
	bool Hep_Physics_Raycast(glm::vec3* origin, glm::vec3* direction, float maxDistance, RaycastHit* hit);
	MonoArray* Hep_Physics_OverlapBox(glm::vec3* origin, glm::vec3* halfSize);
	MonoArray* Hep_Physics_OverlapCapsule(glm::vec3* origin, float radius, float halfHeight);
	MonoArray* Hep_Physics_OverlapSphere(glm::vec3* origin, float radius);
	int32_t Hep_Physics_OverlapBoxNonAlloc(glm::vec3* origin, glm::vec3* halfSize, MonoArray* outColliders);
	int32_t Hep_Physics_OverlapCapsuleNonAlloc(glm::vec3* origin, float radius, float halfHeight, MonoArray* outColliders);
	int32_t Hep_Physics_OverlapSphereNonAlloc(glm::vec3* origin, float radius, MonoArray* outColliders);

	// Entity
	void Hep_Entity_CreateComponent(uint64_t entityID, void* type);
	bool Hep_Entity_HasComponent(uint64_t entityID, void* type);
	uint64_t Hep_Entity_FindEntityByTag(MonoString* tag);

	void Hep_TransformComponent_GetTransform(uint64_t entityID, TransformComponent* outTransform);
	void Hep_TransformComponent_SetTransform(uint64_t entityID, TransformComponent* inTransform);
	void Hep_TransformComponent_GetTranslation(uint64_t entityID, glm::vec3* outTranslation);
	void Hep_TransformComponent_SetTranslation(uint64_t entityID, glm::vec3* inTranslation);
	void Hep_TransformComponent_GetRotation(uint64_t entityID, glm::vec3* outRotation);
	void Hep_TransformComponent_SetRotation(uint64_t entityID, glm::vec3* inRotation);
	void Hep_TransformComponent_GetScale(uint64_t entityID, glm::vec3* outScale);
	void Hep_TransformComponent_SetScale(uint64_t entityID, glm::vec3* inScale);

	void* Hep_MeshComponent_GetMesh(uint64_t entityID);
	void Hep_MeshComponent_SetMesh(uint64_t entityID, Ref<Mesh>* inMesh);

	void Hep_RigidBody2DComponent_ApplyLinearImpulse(uint64_t entityID, glm::vec2* impulse, glm::vec2* offset, bool wake);
	void Hep_RigidBody2DComponent_GetLinearVelocity(uint64_t entityID, glm::vec2* outVelocity);
	void Hep_RigidBody2DComponent_SetLinearVelocity(uint64_t entityID, glm::vec2* velocity);

	RigidBodyComponent::Type Hep_RigidBodyComponent_GetBodyType(uint64_t entityID);
	void Hep_RigidBodyComponent_AddForce(uint64_t entityID, glm::vec3* force, ForceMode foceMode);
	void Hep_RigidBodyComponent_AddTorque(uint64_t entityID, glm::vec3* torque, ForceMode forceMode);
	void Hep_RigidBodyComponent_GetLinearVelocity(uint64_t entityID, glm::vec3* outVelocity);
	void Hep_RigidBodyComponent_SetLinearVelocity(uint64_t entityID, glm::vec3* velocity);
	void Hep_RigidBodyComponent_GetAngularVelocity(uint64_t entityID, glm::vec3* outVelocity);
	void Hep_RigidBodyComponent_SetAngularVelocity(uint64_t entityID, glm::vec3* velocity);
	void Hep_RigidBodyComponent_Rotate(uint64_t entityID, glm::vec3* rotation);
	uint32_t Hep_RigidBodyComponent_GetLayer(uint64_t entityID);
	float Hep_RigidBodyComponent_GetMass(uint64_t entityID);
	void Hep_RigidBodyComponent_SetMass(uint64_t entityID, float mass);

	// Renderer
	// Texture2D
	void* Hep_Texture2D_Constructor(uint32_t width, uint32_t height);
	void Hep_Texture2D_Destructor(Ref<Texture2D>* _this);
	void Hep_Texture2D_SetData(Ref<Texture2D>* _this, MonoArray* inData, int32_t count);

	// Material
	void Hep_Material_Destructor(Ref<Material>* _this);
	void Hep_Material_SetFloat(Ref<Material>* _this, MonoString* uniform, float value);
	void Hep_Material_SetTexture(Ref<Material>* _this, MonoString* uniform, Ref<Texture2D>* texture);

	void Hep_MaterialInstance_Destructor(Ref<MaterialInstance>* _this);
	void Hep_MaterialInstance_SetFloat(Ref<MaterialInstance>* _this, MonoString* uniform, float value);
	void Hep_MaterialInstance_SetVector3(Ref<MaterialInstance>* _this, MonoString* uniform, glm::vec3* value);
	void Hep_MaterialInstance_SetVector4(Ref<MaterialInstance>* _this, MonoString* uniform, glm::vec4* value);
	void Hep_MaterialInstance_SetTexture(Ref<MaterialInstance>* _this, MonoString* uniform, Ref<Texture2D>* texture);

	// Mesh
	Ref<Mesh>* Hep_Mesh_Constructor(MonoString* filepath);
	void Hep_Mesh_Destructor(Ref<Mesh>* _this);
	Ref<Material>* Hep_Mesh_GetMaterial(Ref<Mesh>* inMesh);
	Ref<MaterialInstance>* Hep_Mesh_GetMaterialByIndex(Ref<Mesh>* inMesh, int index);
	int Hep_Mesh_GetMaterialCount(Ref<Mesh>* inMesh);

	void* Hep_MeshFactory_CreatePlane(float width, float height);
}
