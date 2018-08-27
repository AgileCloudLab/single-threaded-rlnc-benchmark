#pragma once

#include <cstdint>
#include <vector>

#include <string>
#include <sstream>

namespace standard_encoder
{
namespace readers
{
class config
{
public:
    config(){}

    config(std::vector<uint32_t> config_vector)
    {
        m_iterations = config_vector.at(0);
        m_threads = config_vector.at(1);
        m_generation_size = config_vector.at(2);
        m_symbol_size = config_vector.at(3);
        m_finite_field = config_vector.at(4);
        // 0 = False, everything else is true
        m_systematic_on = (config_vector.at(5) == 0) ? false : true;

    }

    uint32_t symbol_size() {return m_symbol_size;}

    uint32_t generation_size() {return m_generation_size;}

    uint32_t iterations() {return m_iterations;}

    uint32_t threads() {return m_threads;}

    uint32_t finite_field() {return m_finite_field;}

    bool systematic_on() {return m_systematic_on;}

    std::string to_string()
    {
        std::stringstream stream;
        stream << "Iterations: " << m_iterations << " ";
        stream << "Threads: " << m_threads << " ";
        stream << "Generation size:: " << m_generation_size << " ";
        stream << "Symbol size: " << m_iterations << " ";
        stream << "Finite field: " << m_finite_field << " ";
        stream << "Systematic On: " << m_systematic_on << std::endl;
        return stream.str();
    }

private:
    uint32_t m_symbol_size;
    uint32_t m_generation_size;
    uint32_t m_iterations;
    uint32_t m_threads;
    uint32_t m_finite_field;
    bool m_systematic_on;
};
}
}
