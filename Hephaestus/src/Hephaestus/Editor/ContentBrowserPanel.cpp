#include "heppch.h"
#include "ContentBrowserPanel.h"
#include "Hephaestus/Core/Application.h"
#include "AssetEditorPanel.h"
#include "Hephaestus/Core/Input.h"

#include <imgui_internal.h>

namespace Hep
{
	ContentBrowserPanel::ContentBrowserPanel()
	{
		AssetManager::SetAssetChangeCallback([&]()
		{
			UpdateCurrentDirectory(m_CurrentDirHandle);
		});

		m_FileTex = AssetManager::GetAsset<Texture2D>("assets/editor/file.png");
		m_AssetIconMap[""] = AssetManager::GetAsset<Texture2D>("assets/editor/folder.png");
		m_AssetIconMap["fbx"] = AssetManager::GetAsset<Texture2D>("assets/editor/fbx.png");
		m_AssetIconMap["obj"] = AssetManager::GetAsset<Texture2D>("assets/editor/obj.png");
		m_AssetIconMap["wav"] = AssetManager::GetAsset<Texture2D>("assets/editor/wav.png");
		m_AssetIconMap["cs"] = AssetManager::GetAsset<Texture2D>("assets/editor/csc.png");
		m_AssetIconMap["png"] = AssetManager::GetAsset<Texture2D>("assets/editor/png.png");
		m_AssetIconMap["hsc"] = AssetManager::GetAsset<Texture2D>("assets/editor/hazel.png");

		m_BackbtnTex = AssetManager::GetAsset<Texture2D>("assets/editor/btn_back.png");
		m_FwrdbtnTex = AssetManager::GetAsset<Texture2D>("assets/editor/btn_fwrd.png");

		m_BaseDirectoryHandle = AssetManager::GetAssetHandleFromFilePath("assets");
		m_BaseDirectory = AssetManager::GetAsset<Directory>(m_BaseDirectoryHandle);
		UpdateCurrentDirectory(m_BaseDirectoryHandle);

		memset(m_RenameBuffer, 0, MAX_INPUT_BUFFER_LENGTH);
		memset(m_SearchBuffer, 0, MAX_INPUT_BUFFER_LENGTH);
	}

	void ContentBrowserPanel::DrawDirectoryInfo(AssetHandle directory)
	{
		const Ref<Directory>& dir = AssetManager::GetAsset<Directory>(directory);

		if (ImGui::TreeNode(dir->FileName.c_str()))
		{
			for (AssetHandle child : dir->ChildDirectories)
				DrawDirectoryInfo(child);
			ImGui::TreePop();
		}

		// Only works when TreeNode is open and doesn't have any child TreeNodes. Most likely a bug with ImGui
		if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
			UpdateCurrentDirectory(directory);
	}

	static int s_ColumnCount = 11;
	void ContentBrowserPanel::OnImGuiRender()
	{
		ImGui::Begin("Content Browser", NULL, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);
		{
			UI::BeginPropertyGrid();
			ImGui::SetColumnOffset(1, 240);

			ImGui::BeginChild("##folders_common");
			{
				if (ImGui::CollapsingHeader("Content", nullptr, ImGuiTreeNodeFlags_DefaultOpen))
				{
					for (AssetHandle child : m_BaseDirectory->ChildDirectories)
					{
						DrawDirectoryInfo(child);
					}
				}
			}
			ImGui::EndChild();

			ImGui::NextColumn();

			ImGui::BeginChild("##directory_structure", ImVec2(0, ImGui::GetWindowHeight() - 65));
			{
				ImGui::BeginChild("##top_bar", ImVec2(0, 30));
				{
					RenderBreadCrumbs();
				}
				ImGui::EndChild();

				ImGui::Separator();

				ImGui::BeginChild("Scrolling");
				{
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.3f, 0.3f, 0.35f));

					if (Input::IsKeyPressed(KeyCode::Escape) || (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !m_IsAnyItemHovered))
					{
						m_SelectedAssets.Clear();
						m_RenamingSelected = false;
						memset(m_RenameBuffer, 0, MAX_INPUT_BUFFER_LENGTH);
					}

					m_IsAnyItemHovered = false;

					if (ImGui::BeginPopupContextWindow(0, 1, false))
					{
						if (ImGui::BeginMenu("Create"))
						{
							if (ImGui::MenuItem("Folder"))
							{
								bool created = FileSystem::CreateFolder(m_CurrentDirectory->FilePath + "/New Folder");

								if (created)
								{
									UpdateCurrentDirectory(m_CurrentDirHandle);
									auto createdDirectory = AssetManager::GetAsset<Directory>(
										AssetManager::GetAssetHandleFromFilePath(m_CurrentDirectory->FilePath + "/New Folder"));
									m_SelectedAssets.Select(createdDirectory->Handle);
									memset(m_RenameBuffer, 0, MAX_INPUT_BUFFER_LENGTH);
									memcpy(m_RenameBuffer, createdDirectory->FileName.c_str(), createdDirectory->FileName.size());
									m_RenamingSelected = true;
								}
							}

							if (ImGui::MenuItem("Physics Material"))
							{
								AssetManager::CreateNewAsset<PhysicsMaterial>("New Physics Material.hpm", AssetType::PhysicsMat,
									m_CurrentDirHandle, 0.6f, 0.6f, 0.0f);
								UpdateCurrentDirectory(m_CurrentDirHandle);
							}

							ImGui::EndMenu();
						}

						if (ImGui::MenuItem("Refresh"))
						{
							UpdateCurrentDirectory(m_CurrentDirHandle);
						}

						ImGui::EndPopup();
					}

					ImGui::Columns(s_ColumnCount, nullptr, false);

					for (Ref<Asset>& asset : m_CurrentDirFolders)
					{
						RenderAsset(asset);
						ImGui::NextColumn();
					}

					for (Ref<Asset>& asset : m_CurrentDirFiles)
					{
						RenderAsset(asset);
						ImGui::NextColumn();
					}

					if (m_UpdateDirectoryNextFrame)
					{
						UpdateCurrentDirectory(m_CurrentDirHandle);
						m_UpdateDirectoryNextFrame = false;
					}

					if (m_IsDragging && !ImGui::IsMouseDragging(ImGuiMouseButton_Left, 0.1f))
					{
						m_IsDragging = false;
					}

					ImGui::PopStyleColor(2);
				}
				ImGui::EndChild();
			}
			ImGui::EndChild();

			RenderBottomBar();

			UI::EndPropertyGrid();
		}
		ImGui::End();
	}

	void ContentBrowserPanel::RenderAsset(Ref<Asset>& asset)
	{
		// These caches are currently required for when we change directories
		AssetHandle assetHandle = asset->Handle;
		std::string filename = asset->FileName;

		ImGui::PushID(&asset->Handle);
		ImGui::BeginGroup();

		Ref<Image2D> iconRef = m_AssetIconMap.find(asset->Extension) != m_AssetIconMap.end()
								   ? m_AssetIconMap[asset->Extension]->GetImage()
								   : m_FileTex->GetImage();

		bool selected = m_SelectedAssets.IsSelected(assetHandle);

		if (selected)
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.25f, 0.25f, 0.25f, 0.75f));

		float buttonWidth = ImGui::GetColumnWidth() - 15.0f;
		UI::ImageButton(iconRef, { buttonWidth, buttonWidth });

		if (selected)
			ImGui::PopStyleColor();

		HandleDragDrop(iconRef, asset);

		if (ImGui::IsItemHovered())
		{
			m_IsAnyItemHovered = true;

			if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				if (asset->Type == AssetType::Directory)
				{
					m_PrevDirHandle = m_CurrentDirHandle;
					m_CurrentDirHandle = assetHandle;
					m_UpdateDirectoryNextFrame = true;
				}
				else if (asset->Type == AssetType::Scene)
				{
					// TODO: Open scene in viewport
				}
				else
				{
					AssetEditorPanel::OpenEditor(asset);
				}
			}

			if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !m_IsDragging)
			{
				if (!Input::IsKeyPressed(KeyCode::LeftControl))
					m_SelectedAssets.Clear();

				if (selected)
					m_SelectedAssets.Deselect(assetHandle);
				else
					m_SelectedAssets.Select(assetHandle);
			}
		}

		bool openDeleteModal = false;

		// TODO: Delete multiple items at once
		if (selected && Input::IsKeyPressed(KeyCode::Delete) && !openDeleteModal && m_SelectedAssets.SelectionCount() == 1)
		{
			openDeleteModal = true;
		}

		if (ImGui::BeginPopupContextItem("ContextMenu"))
		{
			ImGui::Text(asset->FilePath.c_str());

			ImGui::Separator();

			if (ImGui::MenuItem("Rename"))
			{
				m_SelectedAssets.Select(assetHandle);
				memset(m_RenameBuffer, 0, MAX_INPUT_BUFFER_LENGTH);
				memcpy(m_RenameBuffer, filename.c_str(), filename.size());
				m_RenamingSelected = true;
			}

			if (ImGui::MenuItem("Delete"))
				openDeleteModal = true;

			ImGui::EndPopup();
		}

		if (openDeleteModal)
		{
			ImGui::OpenPopup("Delete Asset");
			openDeleteModal = false;
		}

		bool deleted = false;
		if (ImGui::BeginPopupModal("Delete Asset", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			if (asset->Type == AssetType::Directory)
				ImGui::Text("Are you sure you want to delete %s and everything within it?", filename.c_str());
			else
				ImGui::Text("Are you sure you want to delete %s?", filename.c_str());

			float columnWidth = ImGui::GetContentRegionAvailWidth() / 4;

			ImGui::Columns(4, 0, false);
			ImGui::SetColumnWidth(0, columnWidth);
			ImGui::SetColumnWidth(1, columnWidth);
			ImGui::SetColumnWidth(2, columnWidth);
			ImGui::SetColumnWidth(3, columnWidth);
			ImGui::NextColumn();
			if (ImGui::Button("Yes", ImVec2(columnWidth, 0)))
			{
				// Cache this so that we can delete the meta file if the asset was deleted successfully
				std::string filepath = asset->FilePath;
				deleted = FileSystem::DeleteFile(filepath);
				if (deleted)
				{
					FileSystem::DeleteFile(filepath + ".meta");
					AssetManager::RemoveAsset(assetHandle);
					m_UpdateDirectoryNextFrame = true;
				}

				ImGui::CloseCurrentPopup();
			}

			ImGui::NextColumn();
			ImGui::SetItemDefaultFocus();
			if (ImGui::Button("No", ImVec2(columnWidth, 0)))
				ImGui::CloseCurrentPopup();

			ImGui::NextColumn();
			ImGui::EndPopup();
		}

		if (!deleted)
		{
			ImGui::SetNextItemWidth(buttonWidth);

			if (!selected || !m_RenamingSelected)
				ImGui::TextWrapped(filename.c_str());

			if (selected)
				HandleRenaming(asset);
		}

		ImGui::EndGroup();
		ImGui::PopID();
	}

	void ContentBrowserPanel::HandleDragDrop(Ref<Image2D> icon, Ref<Asset>& asset)
	{
		if (asset->Type == AssetType::Directory && m_IsDragging)
		{
			if (ImGui::BeginDragDropTarget())
			{
				auto payload = ImGui::AcceptDragDropPayload("asset_payload");
				if (payload)
				{
					int count = payload->DataSize / sizeof(AssetHandle);

					for (int i = 0; i < count; i++)
					{
						AssetHandle handle = *(((AssetHandle*)payload->Data) + i);
						AssetManager::MoveAsset(handle, asset->Handle);
					}

					m_UpdateDirectoryNextFrame = true;
				}
			}
		}

		if (!m_SelectedAssets.IsSelected(asset->Handle) || m_IsDragging)
			return;

		if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenOverlapped) && ImGui::IsItemClicked(ImGuiMouseButton_Left))
			m_IsDragging = true;

		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
		{
			UI::Image(icon, ImVec2(20, 20));
			ImGui::SameLine();
			ImGui::Text(asset->FileName.c_str());
			ImGui::SetDragDropPayload("asset_payload", m_SelectedAssets.GetSelectionData(),
				m_SelectedAssets.SelectionCount() * sizeof(AssetHandle));
			m_IsDragging = true;
			ImGui::EndDragDropSource();
		}
	}

	void ContentBrowserPanel::RenderBreadCrumbs()
	{
		if (UI::ImageButton(m_BackbtnTex->GetImage(), ImVec2(20, 18)))
		{
			if (m_CurrentDirHandle == m_BaseDirectoryHandle) return;
			m_NextDirHandle = m_CurrentDirHandle;
			m_PrevDirHandle = m_CurrentDirectory->ParentDirectory;
			UpdateCurrentDirectory(m_PrevDirHandle);
		}

		ImGui::SameLine();

		if (UI::ImageButton(m_FwrdbtnTex->GetImage(), ImVec2(20, 18)))
			UpdateCurrentDirectory(m_NextDirHandle);

		ImGui::SameLine();

		{
			ImGui::PushItemWidth(200);
			if (ImGui::InputTextWithHint("", "Search...", m_SearchBuffer, MAX_INPUT_BUFFER_LENGTH))
			{
				if (strlen(m_SearchBuffer) == 0)
				{
					UpdateCurrentDirectory(m_CurrentDirHandle);
				}
				else
				{
					m_CurrentDirFolders = AssetManager::SearchAssets(m_SearchBuffer, m_CurrentDirectory->FilePath, AssetType::Directory);
					m_CurrentDirFiles = AssetManager::SearchAssets(m_SearchBuffer, m_CurrentDirectory->FilePath);
				}
			}

			ImGui::PopItemWidth();
		}

		ImGui::SameLine();

		if (m_UpdateBreadCrumbs)
		{
			m_BreadCrumbData.clear();

			AssetHandle currentHandle = m_CurrentDirHandle;
			while (currentHandle != 0)
			{
				Ref<Directory> dirInfo = AssetManager::GetAsset<Directory>(currentHandle);
				m_BreadCrumbData.push_back(dirInfo);
				currentHandle = dirInfo->ParentDirectory;
			}

			std::reverse(m_BreadCrumbData.begin(), m_BreadCrumbData.end());

			m_UpdateBreadCrumbs = false;
		}

		for (const auto& directory : m_BreadCrumbData)
		{
			if (directory->FileName != "assets")
				ImGui::Text("/");

			ImGui::SameLine();

			ImVec2 textSize = ImGui::CalcTextSize(directory->FileName.c_str());
			if (ImGui::Selectable(directory->FileName.c_str(), false, 0, ImVec2(textSize.x, 22)))
			{
				UpdateCurrentDirectory(directory->Handle);
			}

			ImGui::SameLine();
		}
	}

	void ContentBrowserPanel::RenderBottomBar()
	{
		ImGui::BeginChild("##panel_controls", ImVec2(ImGui::GetColumnWidth() - 12, 30), false,
			ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		{
			ImGui::Separator();

			ImGui::Columns(4, 0, false);

			if (m_SelectedAssets.SelectionCount() == 1)
			{
				const Ref<Asset>& asset = AssetManager::GetAsset<Asset>(m_SelectedAssets[0], false);
				ImGui::Text(asset->FilePath.c_str());
			}
			else if (m_SelectedAssets.SelectionCount() > 1)
			{
				ImGui::Text("%d items selected", m_SelectedAssets.SelectionCount());
			}

			ImGui::NextColumn();
			ImGui::NextColumn();
			ImGui::NextColumn();
			ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
			ImGui::SliderInt("##column_count", &s_ColumnCount, 2, 15);
		}
		ImGui::EndChild();
	}

	void ContentBrowserPanel::HandleRenaming(Ref<Asset>& asset)
	{
		if (m_SelectedAssets.SelectionCount() > 1)
			return;

		if (!m_RenamingSelected && Input::IsKeyPressed(KeyCode::F2))
		{
			memset(m_RenameBuffer, 0, MAX_INPUT_BUFFER_LENGTH);
			memcpy(m_RenameBuffer, asset->FileName.c_str(), asset->FileName.size());
			m_RenamingSelected = true;
		}

		if (m_RenamingSelected)
		{
			ImGui::SetKeyboardFocusHere();
			if (ImGui::InputText("##rename_dummy", m_RenameBuffer, MAX_INPUT_BUFFER_LENGTH, ImGuiInputTextFlags_EnterReturnsTrue))
			{
				AssetManager::Rename(asset->Handle, m_RenameBuffer);
				m_RenamingSelected = false;
				m_SelectedAssets.Clear();
				m_UpdateDirectoryNextFrame = true;
			}
		}
	}

	void ContentBrowserPanel::UpdateCurrentDirectory(AssetHandle directoryHandle)
	{
		m_SelectedAssets.Clear();

		m_UpdateBreadCrumbs = true;
		m_CurrentDirFiles.clear();
		m_CurrentDirFolders.clear();
		m_CurrentDirHandle = directoryHandle;
		m_CurrentDirectory = AssetManager::GetAsset<Directory>(m_CurrentDirHandle);

		std::vector<Ref<Asset>> assets = AssetManager::GetAssetsInDirectory(m_CurrentDirHandle);
		std::sort(assets.begin(), assets.end(), [](const Ref<Asset>& a1, const Ref<Asset>& a2)
		{
			return Utils::ToLower(a1->FileName) < Utils::ToLower(a2->FileName);
		});

		for (auto& asset : assets)
		{
			if (asset->Type == AssetType::Directory)
				m_CurrentDirFolders.push_back(asset);
			else
				m_CurrentDirFiles.push_back(asset);
		}
	}
}
