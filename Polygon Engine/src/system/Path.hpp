#pragma once
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include "Shlwapi.h"
#include <sys/stat.h>

namespace engine {
	namespace system {

		enum PathStatus {
			DIR, FILE, NONEX, UNKOWN
		};

		struct Path {

			
		private:
			std::string m_Path;
			PathStatus m_Status;
			bool m_Absolute;

		public:
			Path(const std::string& path);

		private:
			void InitStatus();

		public:
			Path GetRootPath() const;

			Path GetParentPath() const;

			std::string GetRootDir() const;
			
			std::string GetParentDir() const;

			Path& RemoveFileName();

			Path& RemoveExtension();

			Path& ReplaceFileName(const std::string& fileName);

			Path& ReplaceExtension(const std::string& extension);

			std::string GetFileName() const;

			std::string GetExtension() const;

			bool HasExtension() const;

			bool HasRootDir() const;

			bool HasParentDir() const;

			inline bool IsRelative() const {
				return m_Absolute == false;
			}

			bool IsAbsolute() const {
				return m_Absolute;
			}

			inline bool HasFileName() const {
				return IsFile();
			}

			inline std::string GetPath() const {
				return m_Path;
			}

			inline PathStatus GetStatus() const {
				return m_Status;
			}

			inline bool IsFile() const {
				return m_Status == FILE;
			}

			inline bool IsDirectory() const {
				return m_Status == DIR;
			}

			inline bool Exists() const {
				return m_Status != NONEX;
			}
		};
} }