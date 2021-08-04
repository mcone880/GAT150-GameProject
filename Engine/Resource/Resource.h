#pragma once
#include <string>

namespace MAC {

	class Resource {
	public:
		virtual bool Load(const std::string& filename, void* data = nullptr) = 0;
	};
}