#ifndef COMMON_RELATION_H
#define COMMON_RELATION_H
#include <exception>
#include <string>
class DatabaseLookupError : public std::exception {
public:
    DatabaseLookupError(const std::string &message) : message_(message) {
    }

    const char *what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

#endif