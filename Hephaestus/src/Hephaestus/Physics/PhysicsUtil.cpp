#include "heppch.h"
#include "PhysicsUtil.h"
#include "Hephaestus/Utilities/FileSystem.h"

#include <filesystem>

namespace Hep
{
	physx::PxTransform ToPhysXTransform(const TransformComponent& transform)
	{
		physx::PxQuat r = ToPhysXQuat(glm::normalize(glm::quat(transform.Rotation)));
		physx::PxVec3 p = ToPhysXVector(transform.Translation);
		return physx::PxTransform(p, r);
	}

	physx::PxTransform ToPhysXTransform(const glm::mat4& transform)
	{
		// TODO: don't trust glm::toQuat since it doesn't normalize the scale
		physx::PxQuat r = ToPhysXQuat(glm::normalize(glm::toQuat(transform)));
		physx::PxVec3 p = ToPhysXVector(glm::vec3(transform[3]));
		return physx::PxTransform(p, r);
	}

	physx::PxTransform ToPhysXTransform(const glm::vec3& translation, const glm::vec3& rotation)
	{
		return physx::PxTransform(ToPhysXVector(translation), ToPhysXQuat(glm::quat(rotation)));
	}

	physx::PxMat44 ToPhysXMatrix(const glm::mat4& matrix)
	{
		return *(physx::PxMat44*)&matrix;
	}

	physx::PxVec3 ToPhysXVector(const glm::vec3& vector)
	{
		return *(physx::PxVec3*)&vector;
	}

	physx::PxVec4 ToPhysXVector(const glm::vec4& vector)
	{
		return *(physx::PxVec4*)&vector;
	}

	physx::PxQuat ToPhysXQuat(const glm::quat& quat)
	{
		// Note: PxQuat elements are in a different order than glm::quat!
		return physx::PxQuat(quat.x, quat.y, quat.z, quat.w);
	}

	glm::mat4 FromPhysXTransform(const physx::PxTransform& transform)
	{
		glm::quat rotation = FromPhysXQuat(transform.q);
		glm::vec3 position = FromPhysXVector(transform.p);
		return glm::translate(glm::mat4(1.0F), position) * glm::toMat4(rotation);
	}

	glm::mat4 FromPhysXMatrix(const physx::PxMat44& matrix)
	{
		return *(glm::mat4*)&matrix;
	}

	glm::vec3 FromPhysXVector(const physx::PxVec3& vector)
	{
		return *(glm::vec3*)&vector;
	}

	glm::vec4 FromPhysXVector(const physx::PxVec4& vector)
	{
		return *(glm::vec4*)&vector;
	}

	glm::quat FromPhysXQuat(const physx::PxQuat& quat)
	{
		return *(glm::quat*)&quat;
	}

	physx::PxFilterFlags HepFilterShader(physx::PxFilterObjectAttributes attributes0, physx::PxFilterData filterData0,
		physx::PxFilterObjectAttributes attributes1, physx::PxFilterData filterData1, physx::PxPairFlags& pairFlags,
		const void* constantBlock, physx::PxU32 constantBlockSize)
	{
		if (physx::PxFilterObjectIsTrigger(attributes0) || physx::PxFilterObjectIsTrigger(attributes1))
		{
			pairFlags = physx::PxPairFlag::eTRIGGER_DEFAULT;
			return physx::PxFilterFlag::eDEFAULT;
		}

		pairFlags = physx::PxPairFlag::eCONTACT_DEFAULT;

		if ((filterData0.word0 & filterData1.word1) || (filterData1.word0 & filterData0.word1))
		{
			pairFlags |= physx::PxPairFlag::eNOTIFY_TOUCH_FOUND;
			pairFlags |= physx::PxPairFlag::eNOTIFY_TOUCH_LOST;
			return physx::PxFilterFlag::eDEFAULT;
		}

		return physx::PxFilterFlag::eSUPPRESS;
	}

	void PhysicsMeshSerializer::DeleteIfSerialized(const std::string& filepath)
	{
		std::filesystem::path path = filepath;
		std::string cachePath = "DataCache/Colliders/" + path.filename().string() + ".pxm";
		if (IsSerialized(filepath))
			FileSystem::DeleteFile(cachePath);
	}

	void PhysicsMeshSerializer::SerializeMesh(const std::string& filepath, const Buffer& data)
	{
		std::filesystem::path path = filepath;
		std::string cachePath = "DataCache/Colliders/" + path.filename().string() + ".pxm";

		std::ofstream out(cachePath, std::ios::out | std::ios::binary);
		if (out)
		{
			HEP_CORE_INFO("File Created");
			out.write((const char*)data.Data, data.Size / sizeof(char));
			out.close();
		}
		else
		{
			HEP_CORE_INFO("File Already Exists");
		}
	}

	bool PhysicsMeshSerializer::IsSerialized(const std::string& filepath)
	{
		std::filesystem::path path = filepath;
		std::string cachePath = "DataCache/Colliders/" + path.filename().string() + ".pxm";
		return FileSystem::Exists(cachePath);
	}

	Buffer PhysicsMeshSerializer::DeserializeMesh(const std::string& filepath)
	{
		std::filesystem::path path = filepath;
		std::string cachePath = "DataCache/Colliders/" + path.filename().string() + ".pxm";
		std::ifstream in(cachePath, std::ios::in | std::ios::binary);
		uint32_t size = 0;

		Buffer buffer;

		if (in)
		{
			in.seekg(0, std::ios::end);
			size = in.tellg();
			in.seekg(0, std::ios::beg);

			buffer.Allocate(size);
			in.read((char*)buffer.Data, size / sizeof(char));
			in.close();
		}

		return buffer;
	}
}
