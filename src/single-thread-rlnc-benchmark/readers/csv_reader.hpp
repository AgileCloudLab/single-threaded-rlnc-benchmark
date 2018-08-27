#pragma once

#include <string>
#include <fstream>
#include <cassert>

#include <iostream>

namespace standard_encoder
{
namespace readers
{
class file_reader
{
public:
    file_reader(std::string file_name) : m_file_name(file_name),
                                         m_file_stream(file_name)
    {

    }

    std::string next_line()
    {
        assert(m_file_stream && "File not found");
        std::string line;
        if (std::getline(m_file_stream, line))
        {
            return line;
        }
        else
        {
            return "EOF";
        }

    }

private:
    std::string m_file_name;
    std::ifstream m_file_stream;
};
}
}
