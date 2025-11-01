module;

#include <stdint.h>

export module Engine.Renderer.World;

import std;

import Engine.Renderer.RenderObject;
import Engine.RendererCore;

export namespace interstellarEngineCore::Renderer {
	//worlds are the world, they can be a level, a map for a shooter or even the whole world for a open world game, and something very simple like the main menu
	//worlds contain renderObjects, lights, cameras, sounds, physics objects, etc.
	struct world {
		//work is progress, only contains renderObjects for now
		std::string worldName = "unnamed world";
		std::vector<renderObject> renderObjects;

		[[nodiscard]] std::vector<vertex> getWorldVertices() const {
			std::vector<vertex> outputVertices;
			size_t totalVerts = 0;
			for (const auto& obj : renderObjects) {
				totalVerts += obj.vertices.size();
			}
			outputVertices.reserve(totalVerts);

			for (const auto& obj : renderObjects) {
				outputVertices.insert(outputVertices.end(), obj.vertices.begin(), obj.vertices.end());
			}
			return outputVertices;
		}

		[[nodiscard]] std::vector<uint32_t> getWorldIndices() const {
			std::vector<uint32_t> outputIndices;
			uint32_t vertexOffset = 0;
			for (const auto& obj : renderObjects) {
				outputIndices.reserve(outputIndices.size() + obj.indices.size());
				for (uint32_t i : obj.indices) {
					outputIndices.push_back(i + vertexOffset);
				}
				vertexOffset += static_cast<uint32_t>(obj.vertices.size());
			}
			return outputIndices;
		}

	};
}