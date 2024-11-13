#pragma once

#include <stdexcept>
#include <string>

enum class ExceptionType {
    FILE_ERROR,
    NETWORK_ERROR,
    GAME_ERROR,
    UNKNOWN_ERROR
};

class GameException : public std::exception {
public:
    GameException(const std::string& message, ExceptionType type);
    const char* what() const throw();
    ExceptionType getType() const;

private:
    std::string message_;
    ExceptionType type_;
};
