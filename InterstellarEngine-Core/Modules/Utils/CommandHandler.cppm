module;

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

export module Engine.Utils.CommandHandler;

import std;

import Engine.Renderer.Window;
import Engine.Utils.Logger;
import InterstellarEngine_Core;

export namespace interstellarEngineCore::utils {

	void commandHandlerLoop() {
		static std::string command;
		while (true) {
			std::getline(std::cin, command);

			std::clog << "command processed: " << command << "\n";

			if (command == ":exit" or command == ":quit") {
				logLOG("Exiting interstellar engine...\n");
				shouldClose = true;
			}
		}
	}
}