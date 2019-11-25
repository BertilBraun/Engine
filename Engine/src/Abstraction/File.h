#pragma once

#include "CommonTypes.h"

#include <fstream>
#include <filesystem>

namespace Engine
{
	class File {
	public:

		static bool WriteAllText(const String& filePath, const String& text) {
			return WriteToFile(filePath, { text }, std::ios::out);
		}

		static bool WriteAllLines(const String& filePath, const Vector<String>& lines) {
			return WriteToFile(filePath, lines, std::ios::out);
		}

		static bool AppendText(const String& filePath, const String& text) {
			return WriteToFile(filePath, { text }, std::ios::app);
		}

		static bool AppendLines(const String& filePath, const Vector<String>& lines) {
			return WriteToFile(filePath, lines, std::ios::app);
		}

		static String ReadAllText(const String& filePath) {
			std::ifstream f(filePath, std::ios::ate);

			if (!f.good())
				return "";

			std::streampos size = f.tellg();
			char* memblock = new char[size];
			f.seekg(0, std::ios::beg);
			f.read(memblock, size);
			f.close();

			String s = std::move(memblock);

			delete[] memblock;

			return s;
		}

		static Vector<String> ReadAllLines(const String& filePath) {
			String line;
			Vector<String> data;
			std::ifstream f(filePath, std::ios::beg);

			if (!f.good())
				return data;

			while (getline(f, line))
				data.emplace_back(line);

			f.close();

			return data;
		}

		static TimeStamp SinceLastMod(const String& path)
		{
			namespace fs = std::filesystem;
			using Clock = std::chrono::system_clock;

			if (!fs::exists(path))
				return TimeStamp(-1);

			return TimeStamp(-1);

			//time_t cftime = Clock::to_time_t(fs::last_write_time(path));

			//time_t nowtime = Clock::to_time_t(Clock::now());

			//return TimeStamp((float)Clock::duration(nowtime - cftime).count() * 1000000000);
		}

		static TimeStamp LastMod(const String& path)
		{
			namespace fs = std::filesystem;
			using Clock = std::chrono::system_clock;

			if (!fs::exists(path))
				return TimeStamp(-1);

			return TimeStamp(-1);

			//return TimeStamp((float)Clock::duration(Clock::to_time_t(fs::last_write_time(path))).count() * 1000000000);
		}

		static bool Exists(const String& path) {

			namespace fs = std::filesystem;

			return fs::exists(path);
		}

	private: 
		File() {}

		static bool WriteToFile(const String& filePath, const Vector<String>& lines, std::ios_base::openmode openmode) {

			try {
				std::ofstream f(filePath, openmode);

				if (!f.good())
					return false;

				for (const String& l : lines)
					f << l << "\n";
				f.close();
				return true;
			}
			catch (std::exception) {
				return false;
			}
		}

	};
}