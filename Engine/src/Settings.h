#pragma once

#include "Abstraction/CommonTypes.h"
#include "Abstraction/File.h"

#include "cereal/archives/binary.hpp"

#include <fstream>

#include "Defines.h"

namespace Engine
{
	enum class OS {
		Windows, Mac, Linux, Unknown
	};

	class Settings {
	public:
		static Ref<Settings> Get() {
			static Ref<Settings> instance = MakeRef<Settings>();
			return instance;
		}

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(i);
		}

		int i = 0;

#pragma region OS

#ifdef __linux__ 
		OS ActiveOS = OS::Linux;
#elif _WIN32
		OS ActiveOS = OS::Windows;
#elif __APPLE__
		OS ActiveOS = OS::Mac;
#else
		OS ActiveOS = OS::Unknown;
#endif

#pragma endregion
	};

	class SettingSerilization {
	public:
		static void Load() {
			if (!File::Exists("settings.cereal")) {
				File::WriteAllLines("settings.cereal", {});
				LogWarn("Settings weren't found. Loading Settings Failed!");
				return;
			}

			std::ifstream is("settings.cereal", std::ios::binary);
			cereal::BinaryInputArchive archive(is);
			try
			{
				archive(*Settings::Get());
			}
			catch (const std::exception&)
			{
				LogWarn("Loading Settings Failed!");
			}
		}

		static void Save() {
			std::ofstream os("settings.cereal", std::ios::binary);
			cereal::BinaryOutputArchive archive(os);
			archive(*Settings::Get());
		}

	};

}