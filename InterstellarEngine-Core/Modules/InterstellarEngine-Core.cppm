module;

export module InterstellarEngine_Core; 

import std;

namespace fs = std::filesystem;

export namespace interstellarEngineCore {

	bool shouldClose = false;

	//The working directory is the InterstellarEngine-Editor directory
	const fs::path modelPath("../InterstellarEngine-Core/Assets/Models/viking_room.obj");
	constexpr std::string_view modelTexturePath = "../InterstellarEngine-Core/Assets/Textures/viking_room.png";
	constexpr std::string_view grassTexturePath = "../InterstellarEngine-Core/Assets/Textures/grass_block_side.png";
	constexpr std::string_view capibaraEngineerPath = "../InterstellarEngine-Core/Assets/Textures/capibara_engineer_512x512.png";
	constexpr std::string_view vertexShaderPath = "../InterstellarEngine-Core/Assets/Shaders/vert.spv";
	constexpr std::string_view fragamentShaderPath = "../InterstellarEngine-Core/Assets/Shaders/frag.spv";
	constexpr std::string_view testModelPath = "../InterstellarEngine-Core/Assets/Models/modelTest.obj";
}