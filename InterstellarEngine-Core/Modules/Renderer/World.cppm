module;

export module Engine.Renderer.World;

import std;

import Engine.Renderer.RenderObject;

export namespace interstellarEngineCore::Renderer {
	//worlds are the world, they can be a level, a map for a shooter or even the whole world for a open world game, and something very simple like the main menu
	//worlds contain renderObjects, lights, cameras, sounds, physics objects, etc.
	struct world {	//work is progress, only contains renderObjects for now
		//std::string worldName = "unnamed world"; // again MSVC breaking things, maybe i should compile with clang
		std::vector<renderObject> worldRenderObjects;
	};
}