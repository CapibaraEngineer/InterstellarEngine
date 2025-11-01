import std;

import InterstellarEngine_Core;
import Engine.Renderer;

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

int main() {
	interstellarEngineCore::Renderer::engineRenderer engine;

	try {
		engine.run();
	}
	catch (const std::exception& exception) {
		std::cerr << exception.what() << "\n";
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}