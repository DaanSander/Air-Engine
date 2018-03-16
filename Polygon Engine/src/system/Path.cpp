#include "Path.hpp"

namespace engine {
	namespace system {

		Path::Path(const std::string& path) : m_Path(path) {
			InitStatus();
		}

		void Path::InitStatus() {
			struct stat buffer;

			if (stat(m_Path.c_str(), &buffer) == 0) {
				if (buffer.st_mode & S_IFDIR)
					m_Status = DIR;
				else if (buffer.st_mode & S_IFREG)
					m_Status = FILE;
				else
					m_Status = UNKOWN;
			} else
				m_Status = NONEX;

			m_Absolute = !PathIsRelative(m_Path.c_str());
		}

		Path Path::GetRootPath() const {
			return Path(m_Path.substr(0, m_Path.find_first_of('\\')));
		}

		Path Path::GetParentPath() const {
			return Path(m_Path.substr(0, m_Path.find_last_of('\\') + 1));
		}

		std::string Path::GetRootDir() const {
			return m_Path.substr(0, m_Path.find_first_of('\\'));
		}

		std::string Path::GetParentDir() const {
			return m_Path.substr(0, m_Path.find_last_of('\\') + 1);
		}

		//With our without extension?
		Path& Path::RemoveFileName() {
			m_Path = m_Path.substr(0, m_Path.find_last_of('\\') + 1);
			InitStatus();
			return *this;
		}

		Path& Path::RemoveExtension() {
			m_Path = m_Path.substr(0, m_Path.find_last_of('.'));
			InitStatus();
			return *this;
		}

		std::string Path::GetFileName() const {
			return m_Path.substr(m_Path.find_last_of('\\'), m_Path.length());
		}

		std::string Path::GetExtension() const {
			return  m_Path.substr(m_Path.find_last_of('.'), m_Path.length());
		}

		Path& Path::ReplaceFileName(const std::string& fileName) {
			std::string extension = GetExtension();
			RemoveFileName();
			m_Path = m_Path + fileName + extension;
			return *this;
		}

		Path& Path::ReplaceExtension(const std::string& extension) {
			RemoveExtension();
			m_Path = m_Path + extension;
			return *this;
		}

		bool Path::HasExtension() const {
			return GetFileName().find(".") != std::string::npos;
		}

		bool Path::HasRootDir() const {
			return PathIsRoot(m_Path.c_str());
		}

		bool Path::HasParentDir() const {
			return GetParentDir() != m_Path;
		}
} }