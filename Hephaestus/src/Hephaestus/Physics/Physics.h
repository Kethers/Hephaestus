#pragma once

#include "Hephaestus/Core/Timestep.h"
#include "Hephaestus/Core/Base.h"
#include "Hephaestus/Scene/Entity.h"

namespace Hep
{
	enum class ForceMode : uint16_t
	{
		Force = 0,
		Impulse,
		VelocityChange,
		Acceleration
	};

	enum class FilterGroup : uint32_t
	{
		Static    = BIT(0),
		Dynamic   = BIT(1),
		Kinematic = BIT(2),
		All       = Static | Dynamic | Kinematic
	};

	struct SceneParams
	{
		glm::vec3 Gravity = { 0.0f, -9.81f, 0.0f };
	};

	struct RaycastHit
	{
		uint64_t EntityID;
		glm::vec3 Position;
		glm::vec3 Normal;
		float Distance;
	};

	class Physics
	{
	public:
		static void Init();
		static void Shutdown();

		static void CreateScene(const SceneParams& params);
		static void CreateActor(Entity e, int entityCount);

		static void Simulate(Timestep ts);

		static void DestroyScene();

		static void* GetPhysicsScene();

		static void ConnectVisualDebugger();
		static void DisconnectVisualDebugger();
	};
}
