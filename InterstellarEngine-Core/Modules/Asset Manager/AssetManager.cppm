module;

#include <stdint.h>

export module Engine.AssetManager;

import std;

import Engine.Utils.Logger;

namespace fs = std::filesystem;

export namespace interstellarEngineCore::assetManager {

	// The assets folder structure is very specific, assets are stored in subfolders according to their types and only in subfolders, assets in the root will be ignored. 
	// As long the folder follows this rules the assets folder may be any folder in the system
	constexpr std::string_view assetsFolder = "../InterstellarEngine-Core/Assets";
	//scans the asset folder for every valid asset and index them
	void initAssetManager() {
		utils::logLOG(std::format("initializing asset manager, starting in root folder: {}", assetsFolder));
		for (const auto& entry : fs::directory_iterator(assetsFolder)) {
			if (fs::is_regular_file(entry.path())) { 
				std::cout << "\t";
				utils::logWARN(std::format("found asset in root, assets in root will not be loaded, insert asset in proper subfolder. asset: {}", entry.path().filename().string()));
			}
			else if (fs::is_directory(entry.path())) {
				std::cout << "\t";
				utils::logLOG(std::format("found directory [ {} ] in root", entry.path().filename().generic_string()));
				for (const auto& subEntry : fs::recursive_directory_iterator(fs::absolute(entry.path()).string())) {
					std::cout << "\t\t";
					utils::logLOG(std::format("found: {} ", fs::absolute(subEntry.path()).generic_string()));
				}
			}
			else {
				std::cout << "\t";
				utils::logLOG(std::format("found something of unknown type in root, absolute path: {} ", fs::absolute(entry.path()).generic_string()));
			}
		}

		utils::logOK("Asset Manager initialized", "AssetManager.initAssetManager()");
	}

}