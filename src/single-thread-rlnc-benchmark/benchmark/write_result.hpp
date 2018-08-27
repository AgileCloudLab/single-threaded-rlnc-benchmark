#pragma once

#include "result.hpp"
#include "../readers/config.hpp"

#include <string>
#include <sstream>

#include <ctime>

#include <iostream>
#include <fstream>

namespace stdard_encoder
{
namespace benchmark
{
    std::string generate_path(std::string result_path, std::string experiment_name, readers::config& config)
    {
        std::time_t t = std::time(nullptr);
        auto timestamp = static_cast<uint64_t>(t);

        std::stringstream ss;

        ss << result_path << "/" << timestamp << "_" << experiment_name <<
            "_" << config.threads() << "_" << config.generation_size() <<
            "_" << config.symbol_size();

        // Cast the content of ss to a string
        return ss.str();
    }

    std::string convert_to_json_array(std::vector<result> results)
    {
        std::stringstream stream;
        stream << "[" << std::endl;
        for (auto res : results)
        {
            stream << res.to_json_string() << std::endl;
        }
        stream << "]";
        return stream.str();
    }

    bool write_results(std::string file_path, std::vector<result> results)
    {
        std::ofstream result_file;
        result_file.open(file_path);
        result_file << convert_to_json_array(results);
        result_file.close();
        return true;
    }
}
}
