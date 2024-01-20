#pragma once

#ifdef HEP_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif
	#include <Windows.h>
#endif

#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <functional>
#include <memory>
#include <random>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <sstream>

#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <Hephaestus/Core/Application.h>
#include <Hephaestus/Core/Assert.h>
#include <Hephaestus/Core/Base.h>
#include <Hephaestus/Core/Events/Event.h>
#include <Hephaestus/Core/Log.h>
#include <Hephaestus/Core/Math/Mat4.h>
// #include <Hephaestus/Core/Memory.h>
// #include <Hephaestus/Core/Delegate.h>
