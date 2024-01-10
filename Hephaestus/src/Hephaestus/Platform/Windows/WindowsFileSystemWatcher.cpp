#include "heppch.h"
#include "Hephaestus/Utilities/FileSystemWatcher.h"

#include <Windows.h>
#include <filesystem>

namespace Hep
{
	FileSystemWatcher::FileSystemChangedCallbackFn FileSystemWatcher::s_Callback;

	static bool s_Watching = true;
	static HANDLE s_WatcherThread;

	void FileSystemWatcher::SetChangeCallback(const FileSystemChangedCallbackFn& callback)
	{
		s_Callback = callback;
	}

	static std::string wchar_to_string(wchar_t* input)
	{
		std::wstring string_input(input);
		std::string converted(string_input.begin(), string_input.end());
		return converted;
	}

	void FileSystemWatcher::StartWatching()
	{
		DWORD threadId;
		s_WatcherThread = CreateThread(NULL, 0, Watch, 0, 0, &threadId);
		HEP_CORE_ASSERT(s_WatcherThread != NULL);
	}

	void FileSystemWatcher::StopWatching()
	{
		s_Watching = false;
		DWORD result = WaitForSingleObject(s_WatcherThread, 5000);
		if (result == WAIT_TIMEOUT)
			TerminateThread(s_WatcherThread, 0);
		CloseHandle(s_WatcherThread);
	}

	unsigned long FileSystemWatcher::Watch(void* param)
	{
		LPCSTR filepath = "assets";
		char* buffer = new char[1024];
		OVERLAPPED overlapped = { 0 };
		HANDLE handle = NULL;
		DWORD bytesReturned = 0;

		ZeroMemory(buffer, 1024);

		handle = CreateFile(
			filepath,
			FILE_LIST_DIRECTORY,
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
			NULL,
			OPEN_EXISTING,
			FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
			NULL
		);

		ZeroMemory(&overlapped, sizeof(overlapped));

		if (handle == INVALID_HANDLE_VALUE)
			HEP_CORE_ERROR("Unable to accquire directory handle: {0}", GetLastError());

		overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

		if (overlapped.hEvent == NULL)
		{
			HEP_CORE_ERROR("CreateEvent failed!");
			return 0;
		}

		while (s_Watching)
		{
			DWORD status = ReadDirectoryChangesW(
				handle,
				buffer,
				1024,
				TRUE,
				FILE_NOTIFY_CHANGE_CREATION | FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME,
				&bytesReturned,
				&overlapped,
				NULL
			);

			if (!status)
				HEP_CORE_ERROR(GetLastError());

			// NOTE: We can't use 'INFINITE' here since that will prevent the thread from closing when we close the editor
			DWORD waitOperation = WaitForSingleObject(overlapped.hEvent, 5000);

			// If nothing changed, just continue
			if (waitOperation != WAIT_OBJECT_0)
				continue;

			std::string oldName;

			for (;;)
			{
				FILE_NOTIFY_INFORMATION& fni = (FILE_NOTIFY_INFORMATION&)*buffer;
				std::filesystem::path fniFilepath = "assets/" + wchar_to_string(fni.FileName);

				FileSystemChangedEvent e;
				e.Filepath = fniFilepath.string();
				e.NewName = fniFilepath.filename().string();
				e.OldName = fniFilepath.filename().string();
				e.IsDirectory = std::filesystem::is_directory(fniFilepath);

				switch (fni.Action)
				{
					case FILE_ACTION_ADDED:
					{
						e.Action = FileSystemAction::Added;
						s_Callback(e);
						break;
					}
					case FILE_ACTION_REMOVED:
					{
						e.Action = FileSystemAction::Delete;
						s_Callback(e);
						break;
					}
					case FILE_ACTION_MODIFIED:
					{
						e.Action = FileSystemAction::Modified;
						s_Callback(e);
						break;
					}
					case FILE_ACTION_RENAMED_OLD_NAME:
					{
						oldName = fniFilepath.filename().string();
						break;
					}
					case FILE_ACTION_RENAMED_NEW_NAME:
					{
						e.OldName = oldName;
						e.Action = FileSystemAction::Rename;
						s_Callback(e);
						break;
					}
				}

				if (!fni.NextEntryOffset)
				{
					ZeroMemory(buffer, 1024);
					break;
				}

				buffer += fni.NextEntryOffset;
			}
		}

		return 0;
	}
}
