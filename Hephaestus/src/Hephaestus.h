//
// Note:	this file is to be included in client applications ONLY
//			NEVER include this file anywhere in the engine codebase
//
#pragma once

#include "Hephaestus/Core/Application.h"
#include "Hephaestus/Core/Log.h"

#include "Hephaestus/Core/Events/Event.h"
#include "Hephaestus/Core/Events/ApplicationEvent.h"
#include "Hephaestus/Core/Events/KeyEvent.h"
#include "Hephaestus/Core/Events/MouseEvent.h"

#include "imgui/imgui.h"

// --- Hephaestus Render API ------------------------------
#include "Hephaestus/Renderer/Renderer.h"
#include "Hephaestus/Renderer/Framebuffer.h"
#include "Hephaestus/Renderer/Buffer.h"
#include "Hephaestus/Renderer/Texture.h"
#include "Hephaestus/Renderer/Shader.h"
#include "Hephaestus/Renderer/Mesh.h"
#include "Hephaestus/Renderer/Camera.h"
// ---------------------------------------------------

// --- Entry Point ------------
#include "Hephaestus/EntryPoint.h"
// ----------------------------
