#pragma once
#include <chrono>
#include <atomic>
#include <iostream>

namespace Engine
{
	class TimeStamp {
	public:
		TimeStamp(float sec)
			: m_Time(sec)
		{ }

		float Sec() {
			return m_Time;
		}

		float Ms() {
			return Sec() / 1000;
		}

		float Ys() {
			return Ms() / 1000;
		}

	private:
		float m_Time;

	};

	class Stopwatch
	{
		using Clock = std::chrono::high_resolution_clock;

		Clock::time_point start_point;
	public:
		Stopwatch() :
			start_point(Clock::now())
		{}

		TimeStamp ElapsedTime() const {
			return TimeStamp((float)std::chrono::duration_cast<Clock::duration>(Clock::now() - start_point).count() * 1000000000);
		}

		TimeStamp Restart() {
			TimeStamp time = ElapsedTime();
			start_point = Clock::now();
			return time;
		}
	};

	class Timer : public Stopwatch {
	public:
		Timer(const char* func) :
			m_Func(func)
		{}

		~Timer() {
			std::cout << ElapsedTime().Ys() * 1000 << "ms : " << m_Func << std::endl;
		}
	private:
		const char* m_Func;
	};
}