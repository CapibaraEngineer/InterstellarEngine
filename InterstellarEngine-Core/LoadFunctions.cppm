module;

#include <glm/glm.hpp>

#include <tiny_obj_loader.h>

export module LoadFunctions;

import std;
import std.compat;
import AssetEntry;
import EngineFileTypes;
import Engine.Utils.Logger;
import Engine.RendererCore;

export namespace interstellarEngineCore::loadFunctions 
{
	[[nodiscard]] fileTypes::modelFile* loadModel(assetManager::assetEntry entry) 
	{
		using namespace Renderer;
		fileTypes::modelFile* model = new fileTypes::modelFile();
		model->vertices.clear();
		model->indices.clear();
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn, err;

		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, entry.filePath.data())) {
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
					uniqueVertices[vertex] = static_cast<uint32_t>(model->vertices.size());
					model->vertices.push_back(vertex);
				}

				model->indices.push_back(uniqueVertices[vertex]);
			}
		}

		utils::log(utils::logLevel::LOG, "model {} ; model shapes size: {}, model materials size: {}, model vertices size: {}, model indices size: {}, model unique vertices size: {}",
			entry.filePath.data(), shapes.size(), materials.size(), model->vertices.size(), model->indices.size(), uniqueVertices.size());

		std::function<void* (assetManager::assetEntry)> func = [model](assetManager::assetEntry) -> void* {
			return model;
			};
		entry.func = func;

		return model;
	}

	void* loadTexture(const std::string& filePath) {
		return nullptr;
	}
}