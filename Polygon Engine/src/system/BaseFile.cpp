#include "BaseFile.hpp"

namespace engine {
	namespace system {

		BaseFile::BaseFile(const Path& path) : m_Path(path) {

		}

		BaseFile::~BaseFile() {

		}

		BaseFile* BaseFile::Open(int32 mode) {
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

		BaseFile* BaseFile::Seek(int32 offset, const Origin& origin) {
			return this;
		}
} }