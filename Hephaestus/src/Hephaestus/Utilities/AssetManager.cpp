﻿#include "heppch.h"
#include "AssetManager.h"

#include <filesystem>

namespace Hep
{
	void AssetTypes::Init()
	{
		s_Types["hsc"] = AssetType::Scene;
		s_Types["fbx"] = AssetType::Mesh;
		s_Types["obj"] = AssetType::Mesh;
		s_Types["png"] = AssetType::Image;
		s_Types["blend"] = AssetType::Mesh;
		s_Types["wav"] = AssetType::Audio;
		s_Types["ogg"] = AssetType::Audio;
		s_Types["cs"] = AssetType::Script;
	}

	size_t AssetTypes::GetAssetTypeID(const std::string& extension)
	{
		for (auto& kv : s_Types)
		{
			if (kv.first == extension)
				return std::hash<std::string>()(extension);
		}

		return -1;
	}

	AssetType AssetTypes::GetAssetTypeFromExtension(const std::string& extension)
	{
		return s_Types.find(extension) != s_Types.end() ? s_Types[extension] : AssetType::Other;
	}

	std::map<std::string, AssetType> AssetTypes::s_Types;

	AssetManager::AssetManager(const AssetsChangeEventFn& callback)
		: m_AssetsChangeCallback(callback)
	{
		FileSystemWatcher::SetChangeCallback(HEP_BIND_EVENT_FN(AssetManager::OnFileSystemChanged));

		m_LoadedAssets = GetDirectoryContents("assets", true);
	}

	std::string AssetManager::ParseFilename(const std::string& filepath, const char* delim)
	{
		std::vector<std::string> out;
		size_t start;
		size_t end = 0;

		while ((start = filepath.find_first_not_of(delim, end)) != std::string::npos)
		{
			end = filepath.find_first_of(delim, start);
			out.push_back(filepath.substr(start, end - start));
		}

		return out[out.size() - 1];
	}

	std::string AssetManager::ParseFileType(const std::string& filename)
	{
		size_t start;
		size_t end = 0;
		std::vector<std::string> out;

		while ((start = filename.find_first_not_of('.', end)) != std::string::npos)
		{
			end = filename.find('.', start);
			out.push_back(filename.substr(start, end - start));
		}

		return out[out.size() - 1];
	}

	void AssetManager::HandleAsset(const std::string& filepath)
	{}

	void AssetManager::ProcessAsset(const std::string& assetPath)
	{
		std::string filename = ParseFilename(assetPath, "/\\");
		std::string filetype = ParseFileType(assetPath);

		if (filetype == "blend")
		{
			ConvertAsset(assetPath, "fbx");
		}
	}

	void AssetManager::ConvertAsset(const std::string& assetPath, const std::string& conversionType)
	{
		// Create a filestream to write a blender python script for conversion of the asset
		// The 'bpy.ops.export_scene.(asset-type-to-convert) function runs blender in background and exports the file'
		std::string path = std::filesystem::temp_directory_path().string();
		std::ofstream fileStream(path + "export.py");

		// Importing the python modules required for the export to work out
		fileStream << "import bpy\n";
		fileStream << "import sys\n";

		if (conversionType == "fbx")
			fileStream << "bpy.ops.export_scene.fbx(filepath=r'" + path + "asset.fbx" + "', axis_forward='-Z', axis_up='Y')\n";

		if (conversionType == "obj")
			fileStream << "bpy.ops.export_scene.obj(filepath=r'" + path + "asset.obj" + "', axis_forward='-Z', axis_up='Y')\n";

		fileStream.close();

		// This section involves creating the command to export the .blend file to the required asset type
		// The command goes something like this..
		// blender.exe D:\Program Files\cube.blend --background --python D:\Program Files\export.py

		// TODO: bad hard-coding
		std::string blender_base_path = R"(C:\Program Files\Blender Foundation\Blender 2.90\blender.exe)";
		std::string p_asset_path = '"' + assetPath + '"';
		std::string p_blender_path = '"' + blender_base_path + '"';
		std::string p_script_path = '"' + path + "export.py" + '"';

		// Creating the actual command that will execute
		std::string convCommand = '"' + p_blender_path + " " + p_asset_path + " --background --python " + p_script_path + "" + '"';

		// Just for debugging
		HEP_CORE_INFO(convCommand.c_str());

		// Fire the above created command
		// TODO: Platform Abstraction!
		system(convCommand.c_str());
	}

	void AssetManager::OnFileSystemChanged(FileSystemChangedEvent e)
	{
		e.NewName = RemoveExtension(e.NewName);
		e.OldName = RemoveExtension(e.OldName);

		if (e.Action == FileSystemAction::Added)
		{
			m_LoadedAssets = GetDirectoryContents("assets", true);
		}

		if (e.Action == FileSystemAction::Modified)
		{
			// TODO(Peter): Re-import asset
		}

		if (e.Action == FileSystemAction::Rename)
		{
			for (auto& entry : m_LoadedAssets)
			{
				if (entry.Filename == e.OldName)
					entry.Filename = e.NewName;
			}
		}

		if (e.Action == FileSystemAction::Delete)
		{
			for (auto it = m_LoadedAssets.begin(); it != m_LoadedAssets.end(); ++it)
			{
				if (it->Filename != e.NewName)
					continue;

				m_LoadedAssets.erase(it);
				break;
			}
		}

		m_AssetsChangeCallback();
	}

	std::vector<DirectoryInfo> AssetManager::GetDirectoryContents(const std::string& filepath, bool recursive)
	{
		std::vector<DirectoryInfo> directories;

		if (recursive)
		{
			for (const auto& entry : std::filesystem::recursive_directory_iterator(filepath))
			{
				bool isDir = std::filesystem::is_directory(entry);
				std::string dir_data = ParseFilename(entry.path().string(), "/\\");
				std::string fileExt = ParseFileType(dir_data);
				directories.emplace_back(dir_data, fileExt, entry.path().string(), !isDir);
			}
		}
		else
		{
			for (const auto& entry : std::filesystem::directory_iterator(filepath))
			{
				bool isDir = std::filesystem::is_directory(entry);
				std::string dir_data = ParseFilename(entry.path().string(), "/\\");
				std::string fileExt = ParseFileType(dir_data);
				directories.emplace_back(dir_data, fileExt, entry.path().string(), !isDir);
			}
		}

		return directories;
	}

	std::vector<DirectoryInfo> AssetManager::SearchFiles(const std::string& query, const std::string& searchPath)
	{
		std::vector<DirectoryInfo> result;

		if (!searchPath.empty())
		{
			for (const auto& entry : m_LoadedAssets)
			{
				if (entry.Filename.find(query) != std::string::npos && entry.AbsolutePath.find(searchPath) != std::string::npos)
				{
					result.push_back(entry);
				}
			}
		}

		return result;
	}

	std::string AssetManager::GetParentPath(const std::string& path)
	{
		return std::filesystem::path(path).parent_path().string();
	}

	std::vector<std::string> AssetManager::GetDirectoryNames(const std::string& filepath)
	{
		std::vector<std::string> result;
		size_t start;
		size_t end = 0;

		while ((start = filepath.find_first_not_of("/\\", end)) != std::string::npos)
		{
			end = filepath.find_first_of("/\\", start);
			result.push_back(filepath.substr(start, end - start));
		}

		return result;
	}

	bool AssetManager::MoveFile(const std::string& originalPath, const std::string& dest)
	{
		std::filesystem::rename(originalPath, dest);
		std::string newPath = dest + "/" + ParseFilename(originalPath, "/\\");
		return std::filesystem::exists(newPath);
	}

	std::string AssetManager::RemoveExtension(const std::string& filename)
	{
		std::string newName;
		size_t end = filename.find_last_of('.');

		newName = filename.substr(0, end);
		return newName;
	}

	std::string AssetManager::StripExtras(const std::string& filename)
	{
		std::vector<std::string> out;
		size_t start;
		size_t end = 0;

		while ((start = filename.find_first_not_of('.', end)) != std::string::npos)
		{
			end = filename.find('.', start);
			out.push_back(filename.substr(start, end - start));
		}

		if (out[0].length() >= 10)
		{
			auto cutFilename = out[0].substr(0, 9) + "...";
			return cutFilename;
		}

		auto filenameLength = out[0].length();
		auto paddingToAdd = 9 - filenameLength;

		std::string newFileName;

		for (int i = 0; i <= paddingToAdd; i++)
		{
			newFileName += " ";
		}

		newFileName += out[0];

		return newFileName;
	}

	void AssetManager::ImportAsset(const std::string assetPath, const std::string& assetName)
	{}
}
