#include <iostream>
#include <stdexcept>
#include <stdlib.h>

import InterstellarEngine_Core;

int main() {
	insterstellarEngineCore::engineCore engine;

	try {

		engine.run();


	}
	catch (const std::exception& exception) {
		std::cerr << exception.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}