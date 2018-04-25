#pragma once
#include <string>
#include <vector>
#include "Path.hpp"
#include "../math/Math.hpp"

#define LOG_LEVEL_INFO 0
#define LOG_LEVEL_WARN 1
#define LOG_LEVEL_ERR  2

//Why use const char* if the log consists of std::string
namespace engine {
	namespace system {

		class Logger {
			std::vector<const char*> m_Log;

		public:
			Logger();

			template<typename T>
			const char* ToString(const T& t) {
				return std::string("Unsupported type" + typeid(T).name()).c_str();
			}

			template<>
			const char* ToString<char>(const char& t) {
				return &t;
			}

			template<>
			const char* ToString<char*>(char* const& t) {
				return t;
			}

			template<>
			const char* ToString<const char*>(const char* const& t) {
				return t;
			}

			template<>
			const char* ToString<bool>(const bool& t) {
				return t ? "true" : "false";
			}

			template<typename... Args>
			void PrintLog(int32 level, Args... args) 

			}

			void LogInternal();

			void Store(Path path);
		};
} }