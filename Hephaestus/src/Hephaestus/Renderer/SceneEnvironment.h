﻿#pragma once

#include "Texture.h"

namespace Hep
{
	class Environment : public Asset
	{
	public:
		Ref<TextureCube> RadianceMap;
		Ref<TextureCube> IrradianceMap;

		Environment() = default;
		Environment(const Ref<TextureCube>& radianceMap, const Ref<TextureCube>& irradianceMap)
			: RadianceMap(radianceMap), IrradianceMap(irradianceMap) {}
	};
}
