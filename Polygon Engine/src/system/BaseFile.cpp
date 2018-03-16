#include "BaseFile.hpp"

namespace engine {
	namespace system {

		BaseFile::BaseFile(const Path& path) : m_Path(path) {

		}

		BaseFile::~BaseFile() {

		}

		BaseFile* BaseFile::Open(int mode) {
			return this;
		}

		void BaseFile::Close() const {

		}

		void* BaseFile::Read() {
			return nullptr;
		}

		BaseFile* BaseFile::Write(const char* data) {
			return this;
		}

		BaseFile* BaseFile::Seek(int offset, const Origin& origin) {
			return this;
		}
} }