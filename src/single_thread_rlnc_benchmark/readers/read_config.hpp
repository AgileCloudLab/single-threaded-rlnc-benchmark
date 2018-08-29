#pragma once

#include "config.hpp"

#include <string>
#include <vector>

namespace standard_encoder
{
namespace readers
{
template<class Reader>
class config_reader
{
public:
    config_reader(Reader reader, std::string config_path) :
        m_reader(reader), m_config_path(config_path) {}

    config_reader(std::string config_path): m_config_path(config_path)
    {
        m_reader = Reader(config_path);
    }


    std::vector<config> read()
    {
        m_reader.set_config_path(m_config_path);
        return m_reader.read();
    }

    void set_reader(Reader reader)
    {
        m_reader = reader;
    }




private:
    Reader m_reader;
    std::string m_config_path;
};
}
}
