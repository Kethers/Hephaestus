﻿#include "heppch.h"
#include "AssetSerializer.h"
#include "Hephaestus/Utilities/StringUtils.h"
#include "Hephaestus/Utilities/FileSystem.h"
#include "Hephaestus/Renderer/Mesh.h"
#include "Hephaestus/Renderer/SceneRenderer.h"

#include "yaml-cpp/yaml.h"

namespace Hep
{
	void AssetSerializer::SerializeAsset(const Ref<Asset>& asset, AssetType type)
	{
		YAML::Emitter out;

		out << YAML::BeginMap;

		// TODO: This implementation will change
		switch (type)
		{
			case AssetType::PhysicsMat:
			{
				Ref<PhysicsMaterial> material = Ref<PhysicsMaterial>(asset);
				out << YAML::Key << "StaticFriction" << material->StaticFriction;
				out << YAML::Key << "DynamicFriction" << material->DynamicFriction;
				out << YAML::Key << "Bounciness" << material->Bounciness;
				break;
			}
		}
		out << YAML::EndMap;

		std::ofstream fout(asset->FilePath);
		fout << out.c_str();
	}

	Ref<Asset> AssetSerializer::LoadAssetInfo(const std::string& filepath, AssetHandle parentHandle, AssetType type)
	{
		Ref<Asset> asset = Ref<Asset>::Create();

		if (type == AssetType::Directory)
			asset = Ref<Directory>::Create();

		std::string extension = Utils::GetExtension(filepath);
		asset->FilePath = filepath;
		std::replace(asset->FilePath.begin(), asset->FilePath.end(), '\\', '/');

		bool hasMeta = FileSystem::Exists(asset->FilePath + ".meta");
		if (hasMeta)
		{
			LoadMetaData(asset);
		}
		else
		{
			asset->Handle = filepath == "assets" ? AssetHandle(0) : AssetHandle();
			asset->FileName = Utils::RemoveExtension(Utils::GetFilename(filepath));
			asset->Extension = Utils::GetExtension(filepath);
			asset->ParentDirectory = parentHandle;
			asset->Type = type;
		}

		asset->ParentDirectory = parentHandle;
		asset->IsDataLoaded = false;

		if (!hasMeta)
			CreateMetaFile(asset);

		return asset;
	}

	Ref<Asset> AssetSerializer::LoadAssetData(Ref<Asset>& asset)
	{
		if (asset->Type == AssetType::Directory)
			return asset;

		Ref<Asset> temp = asset;
		bool loadYAMLData = true;

		switch (asset->Type)
		{
			case AssetType::Mesh:
			{
				if (asset->Extension != "blend")
					asset = Ref<Mesh>::Create(asset->FilePath);
				loadYAMLData = false;
				break;
			}
			case AssetType::Texture:
			{
				asset = Texture2D::Create(asset->FilePath);
				loadYAMLData = false;
				break;
			}
			case AssetType::EnvMap:
			{
				// TODO
				auto [radiance, irradiance] = SceneRenderer::CreateEnvironmentMap(asset->FilePath);
				asset = Ref<Environment>::Create(radiance, irradiance);
				loadYAMLData = false;
				break;
			}
			case AssetType::Scene:
			case AssetType::Audio:
			case AssetType::Script:
			case AssetType::Other:
			{
				loadYAMLData = false;
				break;
			}
		}

		if (loadYAMLData)
		{
			asset = DeserializeYAML(asset);
			HEP_CORE_ASSERT(asset, "Failed to load asset");
		}

		asset->Handle = temp->Handle;
		asset->FilePath = temp->FilePath;
		asset->FileName = temp->FileName;
		asset->Extension = temp->Extension;
		asset->ParentDirectory = temp->ParentDirectory;
		asset->Type = temp->Type;
		asset->IsDataLoaded = true;

		return asset;
	}

	Ref<Asset> AssetSerializer::DeserializeYAML(const Ref<Asset>& asset)
	{
		std::ifstream stream(asset->FilePath);
		std::stringstream strStream;
		strStream << stream.rdbuf();

		YAML::Node data = YAML::Load(strStream.str());

		if (asset->Type == AssetType::PhysicsMat)
		{
			float staticFriction = data["StaticFriction"].as<float>();
			float dynamicFriction = data["DynamicFriction"].as<float>();
			float bounciness = data["Bounciness"].as<float>();

			return Ref<PhysicsMaterial>::Create(staticFriction, dynamicFriction, bounciness);
		}

		return nullptr;
	}

	void AssetSerializer::LoadMetaData(Ref<Asset>& asset)
	{
		std::ifstream stream(asset->FilePath + ".meta");
		std::stringstream strStream;
		strStream << stream.rdbuf();

		YAML::Node data = YAML::Load(strStream.str());
		if (!data["Asset"])
			HEP_CORE_ASSERT(false, "Invalid File Format");

		asset->Handle = data["Asset"].as<uint64_t>();
		asset->FileName = data["FileName"].as<std::string>();
		asset->FilePath = data["FilePath"].as<std::string>();
		asset->Extension = data["Extension"].as<std::string>();
		asset->Type = (AssetType)data["Type"].as<int>();
	}

	void AssetSerializer::CreateMetaFile(const Ref<Asset>& asset)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Asset" << YAML::Value << asset->Handle;
		out << YAML::Key << "FileName" << YAML::Value << asset->FileName;
		out << YAML::Key << "FilePath" << YAML::Value << asset->FilePath;
		out << YAML::Key << "Extension" << YAML::Value << asset->Extension;
		out << YAML::Key << "Directory" << YAML::Value << asset->ParentDirectory;
		out << YAML::Key << "Type" << YAML::Value << (int)asset->Type;
		out << YAML::EndMap;

		std::ofstream fout(asset->FilePath + ".meta");
		fout << out.c_str();
	}
}