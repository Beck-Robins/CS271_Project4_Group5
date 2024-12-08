#ifndef CUSTOMEXCEPTIONS_HPP
#define CUSTOMEXCEPTIONS_HPP

#include <stdexcept>
#include <string>

class EdgeException : public std::runtime_error {
public:
    explicit EdgeException(const std::string& message)
        : std::runtime_error("EdgeException: " + message) {}
};

class VertexException : public std::runtime_error {
public:
    explicit VertexException(const std::string& message)
        : std::runtime_error("VertexException: " + message) {}
};

#endif

