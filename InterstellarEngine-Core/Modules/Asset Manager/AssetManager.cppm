module;

#include <stdint.h>

export module Engine.AssetManager;

import std;

import Engine.Utils.Logger;
import EngineFileTypes;
import LoadFunctions;
import AssetEntry;

namespace fs = std::filesystem;

namespace {
	std::string toLower(std::string str) {
		std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::tolower(c); });
		return str;
	}
}

export namespace interstellarEngineCore::assetManager { //Mnemosyne

	/*Hello, I'm going to explain how this asset manager will work now:
	The files are added by the user of the engine in the assets folder, once added they will be loaded into an engine format, for example any 3D model file will become a .IEMODEL File.
	Those engine formats are optimized to work as best as possible with the engine, and have the best quality possible so no data is lost.
	In the future, I will add a tool to convert files to the engine format, but for now, they are simply a dream.
	The asset manager is a namespace, because I don't think there is a need for multiple instances of the asset manager, but if there is a need for multiple instances it may become a class later on.
	The asset manager will have initialization function that will be called at the start of the engine, this function will scan the assets folder and put it all in a database.
	The database is a simple key value pair, the key is the name of the file (string) and the value is a function pointer.
	When the user wants to load an asset, they will call the load function with the name of the file, the load function will look up the name in the database and call the function pointer associated with that name, 
	the function pointer will then load the file and return a pointer to the loaded asset (the pointer is put there during the initialization of the asset maneger), then replace the pointer in the database with a function pointer that returns the already loaded asset, so the next time the user wants to load the same asset, it will return the already loaded asset instead of loading it again.
	The unload function will work in a similar way, it will look up the name in the database and call the function pointer associated with that name, the function pointer will then unload the asset and replace the funtion pointer in the database with a function pointer that loads the asset again, for the next time the user wants to load the same asset.
	 - Note from the dev: This whole function pointer stuff is just a test. I'm not sure if this is the most efficient way to make sure asset cannot have multiple copys in memory at the same time. maybe a simple boolean flag that indicates if the asset is loaded or not would be better. But i want try this -CapibaraEngineer
	*/

	enum class assetType {
		MODEL = 0,
		TEXTURE = 1,
		SOUND = 2,
		SHADER = 3
	};

	std::map <std::string, assetEntry> assetDB;

	fs::path root = "../InterstellarEngine-Core/Assets";

	std::set<std::string> acceptedAssetTypes = 
	{
		".obj",
		".png"
	};

	bool isAcceptedAsset(const fs::path& p) {
		if (!p.has_extension()) return false;
		auto fileExtension = toLower(p.extension().generic_string());
		return acceptedAssetTypes.find(fileExtension) != acceptedAssetTypes.end();
	}

	void registerAsset(const fs::directory_entry& assetDirectory)
	{
		auto fileExtension = toLower(assetDirectory.path().extension().generic_string());
		if (fileExtension == ".obj")
		{
			assetEntry asset{ assetDirectory.path().generic_string(), loadFunctions::loadModel };
			assetDB.insert({ assetDirectory.path().generic_string(), asset });
		}
		else if (fileExtension == ".png") {
			assetEntry asset{ assetDirectory.path().generic_string(), loadFunctions::loadTexture };
			assetDB.insert({ assetDirectory.path().generic_string(), asset });
		}
	}

	void processFileEntry(const fs::directory_entry& entry) {
		const auto& path = entry.path();
		utils::log(utils::logLevel::LOG, "File: {}", path.generic_string());

		if (!path.has_extension()) {
			utils::log(utils::logLevel::LOG, "Entry: {} has no extension", path.filename().generic_string());
			return;
		}

		if (isAcceptedAsset(path)) {
			utils::log(utils::logLevel::LOG, "Entry: {} is a accepted asset type, loading in database", path.filename().generic_string());
			registerAsset(entry);
		}
		else {
			utils::log(utils::logLevel::LOG, "Entry: {} is not a accepted asset type", path.filename().generic_string());
		}
	}

	void initialize() {
		utils::log(utils::logLevel::LOG, "initializing asset manager");

		try {
			for (const auto& entry : fs::recursive_directory_iterator(root)) {
				const auto& path = entry.path();
				if (fs::is_regular_file(path)) {
					processFileEntry(entry);
				}
				else if (fs::is_directory(path)) {
					utils::log(utils::logLevel::LOG, "Directory: {}", path.generic_string());
				}
				else {
					utils::log(utils::logLevel::LOG, "Other type: {}", path.generic_string());
				}
			}
		}
		catch (const fs::filesystem_error& error) {
			utils::log(utils::logLevel::FAIL, "Fail to access: {}", error.what());
		}
	}
}