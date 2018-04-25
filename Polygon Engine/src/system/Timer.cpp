#include "Timer.hpp"

namespace engine {
	namespace system {

		Timer::Timer() {
			QueryPerformanceCounter(&m_Time);
			QueryPerformanceFrequency(&m_Frequency);
		}

		void Timer::Reset() {
			QueryPerformanceCounter(&m_Time);
		}

		fl64 Timer::Elapsed() const {
			LARGE_INTEGER currentTime;
			QueryPerformanceCounter(&currentTime);

			long long delta = currentTime.QuadPart - m_Time.QuadPart;
			return (delta * (1.0 / m_Frequency.QuadPart));
		}

		fl64 Timer::ElapsedMillis() const {
			LARGE_INTEGER currentTime;
			QueryPerformanceCounter(&currentTime);

			long long delta = currentTime.QuadPart - m_Time.QuadPart;
			return (delta * (1.0 / m_Frequency.QuadPart)) * 1000.0;
		}
} }