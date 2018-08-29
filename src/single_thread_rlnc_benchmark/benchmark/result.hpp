#pragma once

#include <cstdint>
#include <chrono>

#include <string>
#include <sstream>
#include <iostream>

namespace standard_encoder
{
namespace benchmark
{
class result
{
public:
    result(uint32_t iterations, uint32_t threads, uint32_t generation_size,
           uint32_t symbol_size, uint32_t finite_field, bool systematic_on,
           std::chrono::microseconds start, std::chrono::microseconds end) :
        m_iterations(iterations), m_threads(threads),
        m_generation_size(generation_size), m_symbol_size(symbol_size),
        m_finite_field(finite_field), m_systematic_on(systematic_on),
        m_start(start), m_end(end) {}

    uint32_t iterations() {return m_iterations;}
    uint32_t threads() {return m_threads;}
    uint32_t generation_size() {return m_generation_size;}
    uint32_t symbol_size() {return m_symbol_size;}
    uint32_t finite_field() {return m_finite_field;}

    bool systematic_on() {return m_systematic_on;}

    std::chrono::microseconds start() {return m_start;}
    std::chrono::microseconds end() { return m_end;}

    std::string to_json_string()
    {
        std::stringstream stream;

        std::string indent = "    ";
        stream << "{" << std::endl
               << indent << "\"iterations\":" << m_iterations << "," << std::endl
               << indent << "\"threads\":" << m_threads << "," << std::endl
               << indent << "\"symbols\":" << m_generation_size << "," << std::endl
               << indent << "\"symbol_size\":" << m_symbol_size << "," << std::endl
               << indent << "\"finite_field\":" << m_finite_field << "," << std::endl
               << indent << "\"systematic_on\":" << m_systematic_on << "," << std::endl
               << indent << "\"start\":" << m_start.count() << "," << std::endl
               << indent << "\"end\":" << m_end.count() << std::endl
               << "}";
        return stream.str();
    }


private:

    uint32_t m_iterations;
    uint32_t m_threads;
    uint32_t m_generation_size;
    uint32_t m_symbol_size;
    uint32_t m_finite_field;

    bool m_systematic_on;

    std::chrono::microseconds m_start;
    std::chrono::microseconds m_end;
};
}
}
