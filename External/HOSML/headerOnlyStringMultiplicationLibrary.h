#pragma once

#include <string>

std::string operator*(const std::string& text, const int multiplier);

std::string& operator*=(std::string& text, const int multiplier);

#ifdef HOSMLImplementaion //Header Only String Multiplicaiton Library Implementation

std::string operator*(const std::string& text, const int multiplier) {
	std::string outText = text;
	for (int i = 1; i < multiplier; i++) {
		outText = outText + text;
	}
	return outText;
}

std::string& operator*=(std::string& text, const int multiplier) {
	std::string initialText = text;
	for (int i = 1; i < multiplier; i++) {
		text = text + initialText;
	}
	return text;
}

#endif