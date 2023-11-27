#pragma once

//
// Note:	this file is to be included in client applications ONLY
//			NEVER include this file anywhere in the engine codebase
//

#include "Hephaestus/Core/Application.h"
#include "Hephaestus/Core/Layer.h"
#include "Hephaestus/Core/Log.h"

#include "Hephaestus/Core/Timestep.h"

#include "Hephaestus/Core/Input.h"
#include "Hephaestus/Core/KeyCodes.h"
#include "Hephaestus/Core/MouseButtonCodes.h"

#include "Hephaestus/ImGui/ImGuiLayer.h"

// --------- Renderer ----------
#include "Hephaestus/Renderer/Renderer.h"
#include "Hephaestus/Renderer/RenderCommand.h"

#include "Hephaestus/Renderer/Buffer.h"
#include "Hephaestus/Renderer/Shader.h"
#include "Hephaestus/Renderer/Texture.h"
#include "Hephaestus/Renderer/VertexArray.h"

#include "Hephaestus/Renderer/OrthographicCamera.h"
// -----------------------------

// -------- Entry Point --------
#include "Hephaestus/EntryPoint.h"
// -----------------------------
