#pragma once

#include <functional>

namespace Hep
{
	enum class FileSystemAction
	{
		Added, Rename, Modified, Delete
	};

	struct FileSystemChangedEvent
	{
		FileSystemAction Action;
		std::string FilePath;
		std::string OldName;
		std::string NewName;
		bool IsDirectory;
	};

	class FileSystem
	{
	public:
		static bool CreateFolder(const std::string& filepath);

	public:
		using FileSystemChangedCallbackFn = std::function<void(FileSystemChangedEvent)>;

		static void SetChangeCallback(const FileSystemChangedCallbackFn& callback);
		static void StartWatching();
		static void StopWatching();

	private:
		static unsigned long Watch(void* param);

	private:
		static FileSystemChangedCallbackFn s_Callback;
	};
}