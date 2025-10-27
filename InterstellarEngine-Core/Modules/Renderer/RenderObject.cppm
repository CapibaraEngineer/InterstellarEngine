module;

#include <glm/glm.hpp>

#include <tiny_obj_loader.h>

export module Engine.Renderer.RenderObject;

import std;
import Engine.RendererCore;
import Engine.Utils.Logger;

export namespace interstellarEngineCore::Renderer {
	class renderObject {
	public:
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		bool visible = true;
		uint64_t uid = 0; //unique identifier, never copied

		renderObject() = default;

		renderObject(const std::string_view& OBJToConstructTheModel) {
			loadModel(OBJToConstructTheModel);
		}

		renderObject(const renderObject& otherRenderObject) {
			vertices = otherRenderObject.vertices;
			indices = otherRenderObject.indices;
			visible = otherRenderObject.visible;
		}

		//load a model from a OBJ file, the only parameter is the path to the OBJ file, it will overwrite the vertices and indices of the model
		void loadModel(const std::string_view& modelToBeLoadedPath) {
			vertices.clear();
			indices.clear();
			tinyobj::attrib_t attrib;
			std::vector<tinyobj::shape_t> shapes;
			std::vector<tinyobj::material_t> materials;
			std::string warn, err;

			if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, modelToBeLoadedPath.data())) {
				throw std::runtime_error(warn + err);
			}
			utils::logLOG(std::format("model shapes size {}", shapes.size()));
			std::unordered_map<Vertex, uint32_t> uniqueVertices{};

			for (const auto& shape : shapes) {
				utils::logLOG(std::format("shape indice {}", shape.mesh.indices.size()));
				for (const auto& index : shape.mesh.indices) {
					Vertex vertex{};

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

			utils::logLOG(std::format("model {} ; model shapes size: {}, model materials size: {}, model vertices size: {}, model indices size: {}, model unique vertices size: {}", 
				modelToBeLoadedPath.data(), shapes.size(), materials.size(), vertices.size(), indices.size(), uniqueVertices.size()));
		}

		//operators

		void operator=(const renderObject& other) {
			vertices = other.vertices;
			indices = other.indices;
			visible = other.visible;
		}

		bool operator==(const renderObject& other) const {
			return vertices == other.vertices and indices == other.indices and visible == other.visible;
		}

	};
}