#include "FileSystem.h"
#include <filesystem>

namespace MAC {

	void SetFilePath(const std::string& pathName) {
		std::filesystem::current_path(pathName);
	}

	std::string GetFilePath() {
		return std::filesystem::current_path().string();
	}
}