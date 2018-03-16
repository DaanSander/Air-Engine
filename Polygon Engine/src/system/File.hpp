#pragma once
#include "BaseFile.hpp"
#include <stdio.h>

namespace engine {
	namespace system {

		class File : public BaseFile {

			std::FILE* m_Handle;

		public:
			File(const Path& path);

			~File();

			File* Open(int32 mode);

			void Close() const;

			void* Read();

			File* Write(const char* data);

			File* Seek(int32 offset, const Origin& origin);
		};

} }