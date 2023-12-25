//
// Note:	this file is to be included in client applications ONLY
//			NEVER include this file anywhere in the engine codebase
//
#pragma once

#include "Hephaestus/Core/Application.h"
#include "Hephaestus/Core/Log.h"
#include "Hephaestus/Core/Input.h"
#include "Hephaestus/Core/Timestep.h"
#include "Hephaestus/Core/Timer.h"

#include "Hephaestus/Core/Events/Event.h"
#include "Hephaestus/Core/Events/ApplicationEvent.h"
#include "Hephaestus/Core/Events/KeyEvent.h"
#include "Hephaestus/Core/Events/MouseEvent.h"

#include "Hephaestus/Core/Math/AABB.h"
#include "Hephaestus/Core/Math/Ray.h"

#include "imgui/imgui.h"

// --- Hephaestus Render API ------------------------------
#include "Hephaestus/Renderer/Renderer.h"
#include "Hephaestus/Renderer/SceneRenderer.h"
#include "Hephaestus/Renderer/RenderPass.h"
#include "Hephaestus/Renderer/Framebuffer.h"
#include "Hephaestus/Renderer/VertexBuffer.h"
#include "Hephaestus/Renderer/IndexBuffer.h"
#include "Hephaestus/Renderer/Pipeline.h"
#include "Hephaestus/Renderer/Texture.h"
#include "Hephaestus/Renderer/Shader.h"
#include "Hephaestus/Renderer/Mesh.h"
#include "Hephaestus/Renderer/Camera.h"
#include "Hephaestus/Renderer/Material.h"
// ---------------------------------------------------

// Scenes
#include "Hephaestus/Scene/Entity.h"
#include "Hephaestus/Scene/Scene.h"
#include "Hephaestus/Scene/SceneCamera.h"
#include "Hephaestus/Scene/SceneSerializer.h"
#include "Hephaestus/Scene/Components.h"
