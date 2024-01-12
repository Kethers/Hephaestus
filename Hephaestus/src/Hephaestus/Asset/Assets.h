#pragma once

#include "Hephaestus/Core/UUID.h"

namespace Hep
{
	enum class AssetType
	{
		Scene, Mesh, Texture, EnvMap, Audio, Script, PhysicsMat, Other
	};

	using AssetHandle = UUID;

	class Asset : public RefCounted
	{
	public:
		AssetHandle Handle;
		AssetType Type;

		std::string FilePath;
		std::string FileName;
		std::string Extension;
		int ParentDirectory;

		virtual ~Asset() = default;
	};

	class PhysicsMaterial : public Asset
	{
	public:
		float StaticFriction;
		float DynamicFriction;
		float Bounciness;

		PhysicsMaterial() = default;
		PhysicsMaterial(float staticFriction, float dynamicFriction, float bounciness)
			: StaticFriction(staticFriction), DynamicFriction(dynamicFriction), Bounciness(bounciness)
		{}
	};
}
