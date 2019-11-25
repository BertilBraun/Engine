#pragma once

#if defined(_DEBUG)

#include <filesystem>
#include "core/Time.h"
#include "core/Logger.h"

#endif

#pragma region Logging

#if defined(_DEBUG)

#define LogLvl(lvl, ...) { (void)Engine::Logger(lvl, std::filesystem::path(__FILE__).filename().string(), __FUNCTION__, __LINE__, __VA_ARGS__); }

#define LogError(...)	{ LogLvl(Engine::Logger::Error, __VA_ARGS__); __debugbreak(); }
#define LogWarn(...)	LogLvl(Engine::Logger::Warn, __VA_ARGS__);
#define Log(...)		LogLvl(Engine::Logger::Normal, __VA_ARGS__);

#elif defined(RELEASE) || defined(DIST)

#define LogError(...)
#define LogWarn(...)
#define Log(...)

#endif

#pragma endregion

#pragma region Assert

#if defined(_DEBUG)

#define Assert(condition, ...) { if (!(condition)) LogError(__VA_ARGS__); }

#elif defined(RELEASE) || defined(DIST)

#define Assert(condition, ...)

#endif

#pragma endregion

#pragma region Profiling

#if defined(_DEBUG)

#define ProfileScope	Engine::Timer timer__LINE__(__FUNCTION__);

#elif defined(RELEASE) || defined(DIST)

#define ProfileScope

#endif

#pragma endregion
