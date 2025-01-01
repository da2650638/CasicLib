#pragma once

#include "CasicConfig.h"

#include <optional>
#include <memory>

namespace Casic
{
namespace Graphics
{
	struct Image
	{
		std::optional<std::unique_ptr<uint8_t>> Data;
		int Width;
		int Height;
		int Mipmaps;
		int PixelFormat;
	};
}
}