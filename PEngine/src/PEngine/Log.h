#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace PE
{
	class PE_API Log
	{
	public:

		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_clientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	};
}

/* Core Log Macros */
#define PE_CORE_TRACE(...)	::PE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PE_CORE_INFO(...)	::PE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PE_CORE_WARN(...)	::PE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PE_CORE_ERROR(...)	::PE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PE_CORE_FATAL(...)	::PE::Log::GetCoreLogger()->fatal(__VA_ARGS__)

/* Client Log Macros */
#define PE_TRACE(...)		::PE::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PE_INFO(...)		::PE::Log::GetClientLogger()->info(__VA_ARGS__)
#define PE_WARN(...)		::PE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PE_ERROR(...)		::PE::Log::GetClientLogger()->error(__VA_ARGS__)
#define PE_FATAL(...)		::PE::Log::GetClientLogger()->fatal(__VA_ARGS__)