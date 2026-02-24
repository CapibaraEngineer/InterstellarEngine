module;

#include <stdint.h>

export module Engine.AssetManager;

import std;

import Engine.Utils.Logger;
import EngineFileTypes;
import LoadFunctions;
import AssetEntry;

namespace fs = std::filesystem;

namespace registerFunctions {
	
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

	std::vector<std::string> acceptedAssetTypes = {
		".obj",
		".png"
	
	}; //temporary, just to test the file system, will be removed later on

	


	void registerAsset(const fs::directory_entry& assetDirectory) 
	{
		if (assetDirectory.path().extension() == ".obj") 
		{
			assetEntry asset { assetDirectory.path().generic_string(), loadFunctions::loadModel };
			assetDB.insert({ assetDirectory.path().generic_string(), asset});
		}
		else if (assetDirectory.path().extension() == ".png") {
			
		}
	}


	void initialize() {
		utils::log(utils::logLevel::LOG, "initializing asset manager");

		try {
			for (const auto& entry : fs::recursive_directory_iterator(root)) {
				if (fs::is_regular_file(entry.path())) {
					std::cout << "File: " << entry.path().generic_string() << '\n';
					if (entry.path().has_extension()) {
						std::string extension = entry.path().extension().generic_string();
						if (std::find(acceptedAssetTypes.begin(), acceptedAssetTypes.end(), extension) != acceptedAssetTypes.end()) {
							std::cout << "Entry:" << entry.path().filename().generic_string() << " is a accepted asset type, laoding in database" << '\n';
						}
						else {
							std::cout << "Entry:" << entry.path().filename().generic_string() << " is not a accepted asset type" << '\n';
						}
					}
					std::cout << "Entry:" << entry.path().filename().generic_string() << '\n';

					registerAsset(entry);
					

				}
				else if (fs::is_directory(entry.path())) {
					std::cout << "Directory: " << entry.path().generic_string() << '\n';
				}
				else {
					std::cout << "Other type: " << entry.path().generic_string() << '\n';
				}
			}
		}
		catch (const fs::filesystem_error& e) {
			std::cerr << "Fail to access: " << e.what() << '\n';
		}
	}
	


}