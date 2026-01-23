export module Engine.Utils.Logger;

import std;

#define LOGFunc_Nodiscard [[nodiscard("writeLog function return value may not be discarded")]] //because this nodiscard is way to long

export namespace interstellarEngineCore::utils {
	
	enum class logLevel {
		OK = 1,
		LOG = 0,
		WARN = 2,
		FAIL = -1,
		NONE = 99
	};

	template<typename... Args>
	void log(logLevel level, std::format_string<Args...> fmt, Args&&... args)
	{
		const std::string message =
			std::format(fmt, std::forward<Args>(args)...);

		switch (level)
		{
		case logLevel::OK:
			std::clog << "[\033[32mOK\033[0m] " << message << "\n";
			break;
		case logLevel::LOG:
			std::clog << "[\033[94mLOG\033[0m] " << message << "\n";
			break;
		case logLevel::WARN:
			std::cerr << "[\033[93mWARN\033[0m] " << message << "\n";
			break;
		case logLevel::FAIL:
			std::cerr << "[\033[31mFAIL\033[0m] " << message << "\n";
			break;
		case logLevel::NONE:
			std::clog << message << "\n";
			break;
		default:
			break;
		}
	}
	
	template<typename... Args>
	LOGFunc_Nodiscard constexpr std::string writeLog(logLevel level, std::format_string<Args...> fmt, Args&&... args) {

		const std::string message =
			std::format(fmt, std::forward<Args>(args)...);

		switch (level)
		{
		case logLevel::OK:
			return "[\033[32mOK\033[0m] " + std::string(message) + "\n";
		case logLevel::LOG:
			return "[\033[94mLOG\033[0m] " + std::string(message) + "\n";
		case logLevel::WARN:
			return "[\033[93mWARN\033[0m] " + std::string(message) + "\n";
		case logLevel::FAIL:
			return "[\033[31mFAIL\033[0m] " + std::string(message) + "\n";
		case logLevel::NONE:
			return std::string(message) + "\n";
		default:
			return std::string();
		}
	}
}