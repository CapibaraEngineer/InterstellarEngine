module;

#include <glm/glm.hpp>

#include <tiny_obj_loader.h>
#include <stb_image.h>

export module EngineFileTypes;

import std.compat;

import Engine.RendererCore;
import Engine.Utils.Logger;

export namespace interstellarEngineCore::fileTypes {
	//This module defines the structure of the file types used by the engine.

	enum class imagePixelFormat {
		UNDEFINED,
		R8G8B8A8_SRGB,
		R8G8B8A8_UNORM,
		R8G8B8_UNORM
	};

	struct modelFile {
		std::vector<Renderer::vertex> vertices;
		std::vector<uint32_t> indices;

		
	};

	struct imageFile {
		uint32_t width = 0;
		uint32_t height = 0;
		uint32_t channels = 0;     
		uint32_t mipLevels = 1;
		size_t size = 0;
		imagePixelFormat format = imagePixelFormat::UNDEFINED;
		std::shared_ptr <stbi_uc[]> pixelData;
		/*stbi_uc* pixels;*/

		[[nodiscard]] std::size_t byteSize() const noexcept {
			return static_cast<std::size_t>(width) * height * channels;
		}


	};

}