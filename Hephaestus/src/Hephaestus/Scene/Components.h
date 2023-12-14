#pragma once

#include <glm/glm.hpp>

#include "Hephaestus/Renderer/Texture.h"
#include "Hephaestus/Renderer/Mesh.h"
#include "Hephaestus/Renderer/Camera.h"

namespace Hep
{
	struct TagComponent
	{
		std::string Tag;

		operator std::string&() { return Tag; }
		operator const std::string&() const { return Tag; }
	};

	struct TransformComponent
	{
		glm::mat4 Transform;

		operator glm::mat4&() { return Transform; }
		operator const glm::mat4&() const { return Transform; }
	};

	struct MeshComponent
	{
		Ref<Hep::Mesh> Mesh;

		operator Ref<Hep::Mesh>() { return Mesh; }
	};

	struct ScriptComponent
	{
		// TODO: C# script
		std::string ModuleName;
	};

	struct CameraComponent
	{
		//OrthographicCamera Camera;
		Hep::Camera Camera;
		bool Primary = true;

		operator Hep::Camera&() { return Camera; }
		operator const Hep::Camera&() const { return Camera; }
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color = { 1.0f, 1.0f, 1.0f, 1.0f };
		Ref<Texture2D> Texture;
		float TilingFactor = 1.0f;
	};
}
