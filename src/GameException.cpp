#include "header/GameException.h"
#include <string>
#include <iostream>

GameException::GameException(const std::string& message, ExceptionType type) : message_(message), type_(type) {
	std::cerr << message << std::endl;
}
const char* GameException::what() const throw() { return message_.c_str(); }
ExceptionType GameException::getType() const { return type_; }