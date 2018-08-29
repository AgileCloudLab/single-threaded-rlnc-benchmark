#pragma once

#include "config.hpp"
#include "file_reader.hpp"

#include <string>
#include <cassert>
#include <cstdint>
#include <vector>

namespace standard_encoder
{
namespace readers
{
class csv_reader
{

public:
    csv_reader() {}

    csv_reader(std::string config_path) : m_config_path(config_path)
    {
        assert(is_file_supported(config_path) && "File is not supported");
    }

    void set_config_path(std::string config_path)
    {
        assert(is_file_supported(config_path) && "File is not supported");
        m_config_path = config_path;
    }

    std::vector<config> read()
    {
        // Check if the config path is set
        // if it is not terminate program execition
        assert(!m_config_path.empty() && "empty config path");
        auto reader = file_reader(m_config_path);

        // A file can contain multiple configurations
        // It is unknown how many configurations a file contain
        // therefore the space in the vector is not preallocated
        std::vector<config> configs;
        std::string line = "";
        while(line.compare("EOF") != 0)
        {
            line = reader.next_line();
            if (line.compare("EOF") != 0)
            {
                configs.push_back(csv_string_to_config(line));
            }
        }
        return configs;
    }

private:

    std::vector<std::string> split(std::string str,
                                   std::string delim)
    {
        std::vector<std::string> tokens;
        size_t prev = 0;
        size_t pos = 0;
        do
        {
            pos = str.find(delim, prev);
            if (pos == std::string::npos)
            {
                pos = str.length();
            }
            std::string token = str.substr(prev, pos - prev);
            if (!token.empty())
            {
                tokens.push_back(token);
            }
            prev = pos + delim.length();
        }
        while (pos < str.length() && prev < str.length());

        return tokens;
    }

    config csv_string_to_config(std::string csv_line)
    {
        auto config_as_string = split(csv_line, ",");
        std::vector<uint32_t> config_as_int;

        std::string::size_type sz;

        for (auto element : config_as_string)
        {
            auto as_int = std::stoi(element, &sz);
            config_as_int.push_back((uint32_t) as_int);
        }

        return config(config_as_int);
    }

    bool is_file_supported(std::string config_path)
    {
        // If file ends with .CSV it is supported
        // TODO: Add support for files with out file extension
        //       As it is legal for CSV files to not have a file extension
        return (config_path.substr(config_path.find_last_of(".") + 1) == "csv" ||
                config_path.substr(config_path.find_last_of(".") + 1) == "CSV" );
    }
private:

    std::string m_config_path;

};
}
}
