module;

export module AssetEntry;

import std;

export namespace interstellarEngineCore::assetManager
{
	struct assetEntry
	{
		const std::string filePath;
		std::function<void* (assetEntry)> func;
	};
}