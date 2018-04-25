#pragma once
#include "../DataTypes.h"
#include <Windows.h>

namespace engine {
	namespace system {

		struct Timer {
		private:
			LARGE_INTEGER m_Time, m_Frequency;

		public:
			Timer();

			void Reset();

			//In seconds
			fl64 Elapsed() const;

			//In milli seconds
			fl64 ElapsedMillis() const;
		};
} }