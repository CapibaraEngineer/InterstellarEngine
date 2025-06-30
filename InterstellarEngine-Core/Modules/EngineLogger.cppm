export module EngineLogger;

import <iostream>;

export namespace interstellarEngineCore {
	void logOK(std::string message, std::string caller) {
		/*   this function Logs: [OK] message, logged by caller
		 *	Exemple: [OK] image loaded sucessfuly, logged by imageLoader
		*/
		std::clog << "[\033[32mOK\033[0m] " << message << ", logged by " << caller << "\n";;
	}
	void logLOG(std::string message, std::string caller) {
		/*  this function Logs: [LOG] message, logged by caller
		 *	Exemple: [LOG] time to load image: 1s, logged by imageLoader
		*/
		std::clog << "[\033[94mLOG\033[0m] " << message << ", logged by " << caller << "\n";
	}
	void logFAIL(std::string message, std::string caller) {
		/*  this function Logs: [FAIL] message, logged by caller
		 *	Exemple: [FAIL] image falied to load, logged by imageLoader
		*/
		std::cerr << "[\033[31mFAIL\033[0m] " << message << ", logged by " << caller << "\n";;
	}
}