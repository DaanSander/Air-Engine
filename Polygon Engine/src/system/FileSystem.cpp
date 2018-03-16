#include "FileSystem.hpp"

namespace engine {
	namespace system {

		File* FileSystem::Open(const Path& path, int32 mode) const {
			return (new File(path))->Open(mode);
		}

		void FileSystem::Close(const File& file) {
			file.Close();
		}

		std::string FileSystem::ReadText(const Path& path) const {
			std::string out;
			File* file = Open(path, Mode::READ);
			out = std::string((char*)file->Read());
			file->Close();

			return out;
		}

		//std::string FileSystem::ReadText(const Path& path) const {
		//	char* out;
		//	File* file = Open(path, Mode::READ | Mode::BINARY);
		//	out = (char*)file->Read();
		//	file->Close();
		//
		//	return out;
		//}
} }