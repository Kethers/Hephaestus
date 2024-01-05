#pragma once

#include "Hephaestus/Core/Base.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <glm/glm.hpp>

namespace Hep
{
	class Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
} // namespace Hep

template <typename OStream>
OStream& operator<<(OStream& os, const glm::vec3& vec)
{
	return os << '(' << vec.x << ", " << vec.y << ", " << vec.z << ')';
}

template <typename OStream>
OStream& operator<<(OStream& os, const glm::vec4& vec)
{
	return os << '(' << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ')';
}

// Core log macros
#define HEP_CORE_TRACE(...)		::Hep::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HEP_CORE_INFO(...)		::Hep::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HEP_CORE_WARN(...)		::Hep::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HEP_CORE_ERROR(...)		::Hep::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HEP_CORE_FATAL(...)		::Hep::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define HEP_TRACE(...)			::Hep::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HEP_INFO(...)			::Hep::Log::GetClientLogger()->info(__VA_ARGS__)
#define HEP_WARN(...)			::Hep::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HEP_ERROR(...)			::Hep::Log::GetClientLogger()->error(__VA_ARGS__)
#define HEP_FATAL(...)			::Hep::Log::GetClientLogger()->critical(__VA_ARGS__)
