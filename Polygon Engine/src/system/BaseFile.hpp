#pragma once
#include "Path.hpp"

namespace engine {
	namespace system {

		enum Mode {
			READ = 1 << 0,
			WRITE = 1 << 1,
			BINARY = 1 << 2
		};

		enum Origin {
			BEGIN = SEEK_SET,
			CURRENT = SEEK_CUR,
			END = SEEK_END
		};

		class BaseFile {
		protected:
			Path m_Path;

		private:
				BaseFile();
		public:

			BaseFile(const Path& path);
			//Multiple modes

			virtual ~BaseFile() = 0;

			//Can't read and write at the same time
			virtual BaseFile* Open(int32 mode) = 0;

			virtual void Close() const = 0;

			virtual void* Read() = 0;

			virtual BaseFile* Write(const char* data) = 0;

			virtual BaseFile* Seek(int32 offset, const Origin& origin) = 0;

			//Tell implementeren
			//virtual void Tell() = 0;
		};
}}