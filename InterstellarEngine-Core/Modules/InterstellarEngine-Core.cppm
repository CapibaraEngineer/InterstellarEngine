module;

export module InterstellarEngine_Core; 

import std;

export namespace interstellarEngineCore {
    //The working directory is the InterstellarEngine-Editor directory
    const std::string modelPath = "../InterstellarEngine-Core/Assets/Models/viking_room.obj";
    const std::string modelTexturePath = "../InterstellarEngine-Core/Assets/Textures/viking_room.png";
    const std::string grassTexturePath = "../InterstellarEngine-Core/Assets/Textures/grass_block_side.png";
    const std::string capibaraEngineerPath = "../InterstellarEngine-Core/Assets/Textures/capibara_engineer_512x512.png";
    const std::string vertexShaderPath = "../InterstellarEngine-Core/Assets/Shaders/vert.spv";
    const std::string fragamentShaderPath = "../InterstellarEngine-Core/Assets/Shaders/frag.spv";
}