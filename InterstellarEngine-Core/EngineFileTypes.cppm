module;

#include <glm/glm.hpp>

#include <tiny_obj_loader.h>

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

	void loadModel(const std::string_view& modelToBeLoadedPath, modelFile model) {
		modelFile.vertices.clear();
		modelFile.clear();
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn, err;

		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, modelToBeLoadedPath.data())) {
			throw std::runtime_error(warn + err);
		}
		utils::log(utils::logLevel::LOG, "model shapes size {}", shapes.size());
		std::unordered_map<vertex, uint32_t> uniqueVertices{};

		for (const auto& shape : shapes) {
			utils::log(utils::logLevel::LOG, "shape indice {}", shape.mesh.indices.size());
			for (const auto& index : shape.mesh.indices) {
				vertex vertex{};

				vertex.pos = {
					attrib.vertices[3 * index.vertex_index + 0],
					attrib.vertices[3 * index.vertex_index + 1],
					attrib.vertices[3 * index.vertex_index + 2]
				};

				vertex.texCoord = {
					attrib.texcoords[2 * index.texcoord_index + 0],
					1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
				};

				vertex.color = { 1.0f, 1.0f, 1.0f };

				if (uniqueVertices.count(vertex) == 0) {
					uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
					vertices.push_back(vertex);
				}

				indices.push_back(uniqueVertices[vertex]);
			}
		}

		utils::log(utils::logLevel::LOG, "model {} ; model shapes size: {}, model materials size: {}, model vertices size: {}, model indices size: {}, model unique vertices size: {}",
			modelToBeLoadedPath.data(), shapes.size(), materials.size(), model.vertices.size(), model.indices.size(), uniqueVertices.size());
	}

	struct imageFile {
		uint32_t width = 0;
		uint32_t height = 0;
		uint32_t channels = 0;     
		uint32_t mipLevels = 1;
		imagePixelFormat format = imagePixelFormat::UNDEFINED;
		std::vector<unsigned char> pixels;

		[[nodiscard]] std::size_t byteSize() const noexcept {
			return static_cast<std::size_t>(width) * height * channels;
		}

		[[nodiscard]] bool isValid() const noexcept {
			return width > 0 && height > 0 && !pixels.empty() && pixels.size() == byteSize();
		}

	};

}