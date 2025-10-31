module;

#include <stdint.h>

export module Engine.Renderer.World;

import std;

import Engine.Renderer.RenderObject;
import Engine.RendererCore;

export namespace interstellarEngineCore::Renderer {
	//worlds are the world, they can be a level, a map for a shooter or even the whole world for a open world game, and something very simple like the main menu
	//worlds contain renderObjects, lights, cameras, sounds, physics objects, etc.
	struct world 
	{	
		//work is progress, only contains renderObjects for now
		//std::string worldName = "unnamed world"; // again MSVC breaking things, maybe i should compile with clang
		std::vector<renderObject> renderObjects;

		[[nodiscard]] std::vector<vertex> getWorldVertices() const {
			std::vector<vertex> worldVertices;
			for (const auto& renderObjectInWorld : renderObjects) {
				worldVertices.insert(worldVertices.end(), renderObjectInWorld.vertices.begin(), renderObjectInWorld.vertices.end());
			}
			return worldVertices;
		}

		[[nodiscard]] std::vector<uint32_t> getWorldIndices() const {
			std::vector<uint32_t> worldIndices;
			for (const auto& renderObjectInWorld : renderObjects) {
				worldIndices.insert(worldIndices.end(), renderObjectInWorld.indices.begin(), renderObjectInWorld.indices.end());
			}
			return worldIndices;
		}

	};
}