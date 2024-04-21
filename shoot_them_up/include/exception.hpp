#pragma once

#include <exception>
#include <string>

class Exception : public std::exception {
public:
    Exception(const std::string& msg) : message(msg) { }

    std::string getError() const {
        return message;
    }

private:
    std::string message;
};