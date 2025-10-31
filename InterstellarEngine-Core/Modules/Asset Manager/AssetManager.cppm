module;

#include <stdint.h>

export module Engine.AssetManager;

import std;

export namespace interstellarEngineCore::AssetManager {

	struct asset {
		std::string_view assetPath;
		std::string_view assetName; //defined by the developer, for easier access 
		const uint64_t assetUID = 0; //unique identifier, never copied
	};

	struct model
	{
		
	};


	std::vector<asset> assetsList = {
		asset{ "../InterstellarEngine-Core/Assets/Models/viking_room.obj", "viking_room_model", 0},
		asset{ "../InterstellarEngine-Core/Assets/Textures/viking_room.png", "viking_room_texture", 1},
		asset{ "../InterstellarEngine-Core/Assets/Textures/grass_block_side.png", "grass_block_texture", 2},
		asset{ "../InterstellarEngine-Core/Assets/Textures/capibara_engineer_512x512.png", "capibara_engineer_texture", 3},
		asset{ "../InterstellarEngine-Core/Assets/Shaders/vert.spv", "vertex_shader", 4},
		asset{ "../InterstellarEngine-Core/Assets/Shaders/frag.spv", "fragment_shader", 5},
		asset{ "../InterstellarEngine-Core/Assets/Models/modelTest.obj", "model_test", 6}
		
	};

	void addAsset(const std::string_view& path, const std::string_view& name) {
		assetsList.push_back(asset{ path, name, assetsList.size() + 1});
	}

	// removes an asset by its unique identifier, does not free memory, just marks it as removed, 
	// because if it did remove it I would need to actually make proper UID logic and i am lazy
	void removeAssetByUID(uint64_t assetUID) {
		assetsList.at(assetUID).assetName = "removed";
		assetsList.at(assetUID).assetPath = "removed";
	}

}