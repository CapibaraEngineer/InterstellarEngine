module;

#include <glm/glm.hpp>

#include <tiny_obj_loader.h>
#include <stb_image.h>

export module LoadFunctions;

import std;
import std.compat;
import AssetEntry;
import EngineFileTypes;
import Engine.Utils.Logger;
import Engine.RendererCore;

export namespace interstellarEngineCore::loadFunctions 
{
	[[nodiscard]] fileTypes::modelFile* loadModel(assetManager::assetEntry& entry) 
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

		std::function<void* (assetManager::assetEntry&)> func = [model](assetManager::assetEntry&) -> void* {
			std::cout << "Returning already loaded model" << std::endl;
			return model;
			};
		entry.func = func;

		return model;
	}

	[[nodiscard]] void* loadTexture(assetManager::assetEntry& entry) {
		// Aloca imagem do formato do engine
		fileTypes::imageFile* image = new fileTypes::imageFile();

		int imageWidth = 0;
		int imageHeight = 0;
		int imageChannelsInFile = 0;
		// Força 4 canais (RGBA) para compatibilidade com o pipeline atual
		stbi_uc* pixelData = stbi_load(entry.filePath.c_str(), &imageWidth, &imageHeight, &imageChannelsInFile, STBI_rgb_alpha);
		std::shared_ptr<stbi_uc[]> pixelDataPtr(pixelData, stbi_image_free);
		if (!pixelData) {
			delete image;
			throw std::runtime_error(std::string("failed to load texture image: ") + entry.filePath);
		}

		image->width = static_cast<uint32_t>(imageWidth);
		image->height = static_cast<uint32_t>(imageHeight);
		image->channels = 4u; // STBI_rgb_alpha força 4 canais
		image->mipLevels = 1u;
		image->size = image->width * image->height * 4;
		image->format = fileTypes::imagePixelFormat::R8G8B8A8_SRGB;

		
		image->pixelData = pixelDataPtr;


		utils::log(utils::logLevel::OK, "texture loaded: {} ({}x{} channels={})", entry.filePath, image->width, image->height, image->channels);

		// Mantém o mesmo padrão usado em loadModel: substitui a função localmente para retornar o ponteiro já carregado.
		std::function<void* (assetManager::assetEntry&)> func = [image](assetManager::assetEntry&) -> void* {
			std::cout << "Returning already loaded image" << std::endl;
			return image;
			};
		entry.func = func;

		return image;
	}
}