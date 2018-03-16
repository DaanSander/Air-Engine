#pragma once
#include "File.hpp"

namespace engine {
	namespace system {

		class FileSystem {

			//Dynamically allocated
			File* Open(const Path& path, int mode) const;

			void Close(const File& file);

			std::string ReadText(const Path& path) const;

			char* ReadBinary(const Path& path) const;
		};

} }