#pragma once

#include "Abstraction/File.h"
#include "Abstraction/CommonTypes.h"

#include <sstream>
#include <mutex>
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#endif 

#define LOG_FILE_PATH "log.txt"

namespace Engine
{
	static std::mutex Mutex;

	class Logger {
	public:
		enum LoggingLevel {
			Normal,
			Warn,
			Error
		};

	public:
		template<typename... Args>
		Logger(LoggingLevel lvl, const String& fileName, const String& function, int line, Args... args) :
			m_Lvl(lvl),
			m_FileName(fileName),
			m_Function(function),
			m_Line(line)
		{
			std::ostringstream msg;
			Prepare(msg, args...);
		}

	private:
		template<class T, typename... Args>
		void Prepare(std::ostringstream& msg, T value, Args... args)
		{
			msg << ' ' << value;
			Prepare(msg, args...);
		}

		void Prepare(std::ostringstream& msg) {

			auto indent = [](std::ostringstream& of, int s, int e) {
				for (int i = s; i < e; i++)
					of << " ";
			};

			std::ostringstream of;

			String LogInfoDescription;

			switch (m_Lvl)
			{
			case Normal:	LogInfoDescription = "Log"; break;
			case Warn:		LogInfoDescription = "Warn"; break;
			case Error:		LogInfoDescription = "Error"; break;
			}

			of << " [ " << LogInfoDescription;

			indent(of, (int)LogInfoDescription.size(), 10);

			of << "] [ " << m_FileName;

			indent(of, (int)m_FileName.size(), 20);

			of << "] [ " << m_Function;

			indent(of, (int)m_Function.size(), 20);

			of << " : ( line : " << m_Line;

			int s = 0;
			while (m_Line /= 10) s++;

			indent(of, s, 5);

			of << ") ] : " << msg.str();

			Mutex.lock();

#ifdef _WIN32
			WORD color = 0;

			switch (m_Lvl)
			{
			case Normal:	color = 3; break;
			case Warn:		color = 14; break;
			case Error:		color = 12; break;
			}

			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(h, color);
			std::cout << of.str() << std::endl;
			SetConsoleTextAttribute(h, 15);
#else
			std::cout << of.str() << std::endl;
#endif 
			if (m_Lvl == Error)
				File::AppendText(LOG_FILE_PATH, of.str());

			Mutex.unlock();
		}

	private:
		LoggingLevel m_Lvl;
		const String m_FileName;
		const String m_Function;
		int m_Line;
	};

}