#include "block_coder_benchmark.hpp"

#include <cassert>
#include <iostream>
int main(int argc, char** argv)
{

    assert(argc >= 3);
    std::string config_path(argv[1]);

    std::string dest_path(argv[2]);

    std::cout << config_path << std::endl;
    std::cout << dest_path << std::endl;

    standard_encoder::benchmark::run_benchmark(config_path, dest_path);
}
