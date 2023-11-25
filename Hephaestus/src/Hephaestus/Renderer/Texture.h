#pragma once

#include <string>
#include <Hephaestus/Core.h>

namespace Hep
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GeiWidth() const = 0;
		virtual uint32_t GeiHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const std::string& path);
	};
}
