#include "File.hpp"

namespace engine {
	namespace system {

		File::File(const Path& path) : BaseFile(path) {

		}

		File::~File() {
			Close();
		}

		File* File::Open(int mode) {
			std::string strMode;

			if (mode & Mode::READ)
				strMode.append("r");
			if (mode & Mode::WRITE)
				strMode.append("w");
			if (mode & Mode::BINARY)
				strMode.append("b");

			fopen_s(&m_Handle, m_Path.GetPath().c_str(), strMode.c_str());
			return this;
		}

		void File::Close() const {
			fclose(m_Handle);
		}

		//Dynamicly allocated
		void* File::Read() {
			fseek(m_Handle, 0, SEEK_END);
			unsigned int length = ftell(m_Handle);
			fseek(m_Handle, 0, SEEK_SET);

			char* data = new char[length + 1];
			memset(data, 0, length + 1);
			fread(data, length, sizeof(char), m_Handle);

			return data;
		}

		File* File::Write(const char* data) {
			fwrite(data, sizeof(char), sizeof(data), m_Handle);
			return this;
		}
		
		File* File::Seek(int offset, const Origin& origin) {
			fseek(m_Handle, offset, origin);
			return this;
		}
}}