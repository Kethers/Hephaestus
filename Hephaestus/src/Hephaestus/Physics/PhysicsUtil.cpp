﻿#include "heppch.h"
#include "PhysicsUtil.h"

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
		std::filesystem::path p = filepath;
		std::filesystem::path path = p.parent_path() / (p.filename().string() + ".pxm");

		size_t firstDot = path.filename().string().find_first_of('.');
		firstDot = firstDot == std::string::npos ? path.filename().string().length() - 1 : firstDot;
		std::string dirName = p.filename().string().substr(0, firstDot);

		if (IsSerialized(filepath))
			std::filesystem::remove_all(p.parent_path() / dirName);
	}

	void PhysicsMeshSerializer::SerializeMesh(const std::string& filepath, const physx::PxDefaultMemoryOutputStream& data,
		const std::string& submeshName)
	{
		std::filesystem::path p = filepath;
		std::filesystem::path path = p.parent_path() / (p.filename().string() + ".pxm");
		size_t firstDot = path.filename().string().find_first_of('.');
		firstDot = firstDot == std::string::npos ? path.filename().string().length() - 1 : firstDot;
		std::string dirName = p.filename().string().substr(0, firstDot);

		if (submeshName.length() > 0)
			path = p.parent_path() / dirName / (submeshName + ".pxm");

		std::filesystem::create_directory(p.parent_path() / dirName);
		std::string cachedFilepath = path.string();

		HEP_CORE_INFO("Serializing {0}", submeshName);

		std::ofstream out(cachedFilepath, std::ios::out | std::ios::binary);
		if (out)
		{
			HEP_CORE_INFO("File Created");
			out.write((const char*)data.getData(), data.getSize() / sizeof(char));
			out.close();
		}
		else
		{
			HEP_CORE_INFO("File Already Exists");
		}
	}

	bool PhysicsMeshSerializer::IsSerialized(const std::string& filepath)
	{
		std::filesystem::path p = filepath;
		size_t firstDot = p.filename().string().find_first_of(".");
		firstDot = firstDot == std::string::npos ? p.filename().string().length() - 1 : firstDot;
		std::string dirName = p.filename().string().substr(0, firstDot);
		auto path = p.parent_path() / dirName;
		return std::filesystem::is_directory(path);
	}

	static physx::PxU8* s_MeshDataBuffer;

	physx::PxDefaultMemoryInputData PhysicsMeshSerializer::DeserializeMesh(const std::string& filepath, const std::string& submeshName)
	{
		std::filesystem::path p = filepath;
		size_t lastDot = p.filename().string().find_first_of(".");
		lastDot = lastDot == std::string::npos ? p.filename().string().length() - 1 : lastDot;
		std::string dirName = p.filename().string().substr(0, lastDot);
		auto path = p.parent_path() / dirName;
		if (submeshName.length() > 0)
			path = p.parent_path() / dirName / (submeshName + ".pxm");

		std::ifstream in(path.string(), std::ios::in | std::ios::binary);

		uint32_t size = 0;
		if (in)
		{
			in.seekg(0, std::ios::end);
			size = in.tellg();
			in.seekg(0, std::ios::beg);

			if (s_MeshDataBuffer)
				delete[] s_MeshDataBuffer;

			s_MeshDataBuffer = new physx::PxU8[size / sizeof(physx::PxU8)];
			in.read((char*)s_MeshDataBuffer, size / sizeof(char));
			in.close();
		}

		return physx::PxDefaultMemoryInputData(s_MeshDataBuffer, size);
	}
}
