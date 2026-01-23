module;

#include <stdint.h>

export module Engine.AssetManager;

import std;

import Engine.Utils.Logger;

namespace fs = std::filesystem;

//unnamed namespace for implemetations details
namespace {
	// I will come back to these funcitons later, they are just not tha important right now
	//using namespace interstellarEngineCore;
	//void thinkNameLater(const std::string_view& directory, const int recursion) {
	//	for (const auto& entry : fs::directory_iterator(directory)) {
	//		if (fs::is_regular_file(entry.path())) {
	//			for (int i = 0; i < recursion; i++) {
	//				std::cout << "\t";
	//			}
	//			std::cout << "\t";
	//			utils::logLOG(std::format("found: {} ", fs::absolute(entry.path()).generic_string()));
	//		}
	//		else if (fs::is_directory(entry.path())) {
	//			for (int i = 0; i < recursion; i++) {
	//				std::cout << "\t";
	//			}
	//			std::cout << "\t";
	//			utils::logLOG(std::format("found directory [ {} ]", entry.path().filename().generic_string()));
	//			thinkNameLater(entry.path().generic_string(), recursion + 1);
	//		}
	//		else {
	//			for (int i = 0; i < recursion; i++) {
	//				std::cout << "\t";
	//			}
	//			utils::logLOG(std::format("found something of unknown type in {}, absolute path: {} ", directory ,fs::absolute(entry.path()).generic_string()));
	//		}
	//	}
	//}
	//void printDirectoriesRecursively(const std::string_view& rootFolder) {
	//	for (const auto& entry : fs::directory_iterator(rootFolder)) {
	//		if (fs::is_regular_file(entry.path())) {
	//			std::cout << "\t";
	//			utils::logWARN(std::format("found asset in root, assets in root will not be loaded, insert asset in proper subfolder. asset: {}", entry.path().filename().string()));
	//		}
	//		else if (fs::is_directory(entry.path())) {
	//			std::cout << "\t";
	//			utils::logLOG(std::format("found directory [ {} ] in root", entry.path().filename().generic_string()));
	//			
	//			thinkNameLater(entry.path().generic_string(), 1);
	//			
	//		}
	//		else {
	//			std::cout << "\t";
	//			utils::logLOG(std::format("found something of unknown type in root, absolute path: {} ", fs::absolute(entry.path()).generic_string()));
	//		}
	//	}
	//}
}

export namespace interstellarEngineCore::assetManager {

	// The assets folder structure is very specific, assets are stored in subfolders according to their types and only in subfolders, assets in the root will be ignored. 
	// As long the folder follows this rules the assets folder may be any folder in the system
	constexpr std::string_view assetsFolder = "../InterstellarEngine-Core/Assets";

	struct asset {
		std::string assetPath;
		std::string assetFileExtension;

	};

	std::vector<asset> assets;

	//scans the asset folder for every valid asset and index them
	void initAssetManager() {
		utils::log(utils::logLevel::LOG, "initializing asset manager, starting in root folder: {}", assetsFolder);

		try {
			for (const auto& entry : fs::recursive_directory_iterator(assetsFolder)) {
				if (fs::is_regular_file(entry.path())) {
					assets.push_back({ fs::absolute(entry.path()).generic_string(), entry.path().extension().generic_string() });
				}

			}
		}
		catch (const fs::filesystem_error& e) {
			std::cerr << "Erro ao acessar: " << e.what() << "\n";
		}

		for (const auto& assetI : assets) {
			std::cout << assetI.assetPath << "\n";
		}

		utils::log(utils::logLevel::OK, "Asset Manager initialized");
	}

}