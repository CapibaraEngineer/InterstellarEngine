export module Engine.Utils.Logger;

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

	//log without the caller
	void logOK(std::string message) {
		/*  this function Logs: [OK] message
		 *	Exemple: [OK] image loaded sucessfuly
		*/
		std::clog << "[\033[32mOK\033[0m] " << message << "\n";
	}
	void logLOG(std::string message) {
		/*  this function Logs: [LOG] message
		 *	Exemple: [LOG] time to load image: 1s
		*/
		std::clog << "[\033[94mLOG\033[0m] " << message << "\n";
	}
	void logFAIL(std::string message) {
		/*  this function Logs: [FAIL] messager
		 *	Exemple: [FAIL] image falied to load
		*/
		std::cerr << "[\033[31mFAIL\033[0m] " << message << "\n";;
	}
	
}