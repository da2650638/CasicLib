#include "CasicUtils.h"

#include <fstream>

namespace Casic
{
namespace Util
{
	void Deallocate(void* ptr) {
		if (ptr) {
			::free(ptr);
		}
	}
	
	std::tuple<unsigned char*, int> LoadFileData(const char* filename)
	{
		std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
		if (!ifs.is_open()) {
			return { nullptr, -1 };
			//throw std::runtime_error("Failed to open file: " + std::string(filename));
		}

		std::streampos size = ifs.tellg();
		if (size <= 0) {
			return { nullptr, -1 };
			//throw std::runtime_error("Failed to read file or file is empty: " + std::string(filename));
		}

		unsigned char* raw = Allocate<unsigned char>(static_cast<size_t>(size));
		if (!raw) {
			return { nullptr, -1 };
			//throw std::runtime_error("Failed to allocate memory for file: " + std::string(filename));
		}

		ifs.seekg(0, std::ios::beg);
		if (!ifs.read(reinterpret_cast<char*>(raw), size)) {
			//throw std::runtime_error("Failed to read the full file: " + std::string(filename));
			return { nullptr, -1 };
		}

		return { raw, static_cast<int>(size) };
	}

	void UnloadFileData(unsigned char* filedata)
	{
		Deallocate(filedata);
	}
}
}