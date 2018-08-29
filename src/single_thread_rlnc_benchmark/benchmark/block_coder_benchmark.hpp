#pragma once

#include "result.hpp"
#include "write_result.hpp"

#include "../readers/csv_reader.hpp"
#include "../readers/read_config.hpp"
#include "../readers/config.hpp"

#include <storage/storage.hpp>
#include <fifi/default_field.hpp>

#include <kodo_rlnc/coders.hpp>


#include <vector>
#include <ctime>

#include <string>

#include <iostream>

#include <chrono>
#include <thread>

namespace standard_encoder
{
namespace benchmark
{

    result benchmark(readers::config& config)
    {

        srand(static_cast<uint32_t>(time(0)));

        std::vector<uint8_t> data_in(config.generation_size() *
                                     config.symbol_size());

        std::generate(data_in.begin(), data_in.end(), rand);



        fifi::api::field field;

        if (config.finite_field() == 1)
        {
            field = fifi::api::field::binary8;
        } else if (config.finite_field() == 2)
        {
            field = fifi::api::field::binary16;
        } else
        {
            assert(false && "Unsupported finite field"); // MUST TERMINATE
        }

        kodo_rlnc::encoder::factory encoder_factory(field,
                                                    config.generation_size(),
                                                    config.symbol_size());
        auto encoder = encoder_factory.build();
        assert((config.generation_size() * config.symbol_size()) ==
               encoder->block_size());

        encoder->set_const_symbols(storage::storage(data_in));
        if (encoder->has_systematic_mode() && config.systematic_on())
        {
            encoder->set_systematic_off();
        }

        std::vector<uint8_t> payload(encoder->payload_size());



        auto start = std::chrono::high_resolution_clock::now();
        for (uint32_t i = 0; i < config.generation_size(); ++i)
        {
            encoder->write_payload(payload.data());
        }

        auto end = std::chrono::high_resolution_clock::now();

        auto c_start = std::chrono::duration_cast<std::chrono::microseconds>(start.time_since_epoch());
        auto c_end = std::chrono::duration_cast<std::chrono::microseconds>(end.time_since_epoch());

        // Todo: set threads
        return result(config.iterations(), 1, config.generation_size(),
                      config.symbol_size(), config.finite_field(), config.systematic_on(),
                      c_start, c_end);

    }

    void run_benchmark(std::string config_path, std::string result_path)
    {
        auto config_reader = readers::config_reader<readers::csv_reader>(config_path);

        auto configs = config_reader.read();

        uint32_t count = 0;
        for (auto config : configs)
        {
            ++count;
            std::cout << "Start experiment: " << count << " of " << configs.size() << std::endl;
            // We preallocated the result vector, as this is more efficient memory-
            // wise and will have less resource impact when we push a result to
            // the result vector
            std::vector<result> results;
            results.reserve(config.iterations());

            for (uint32_t i = 0; i < config.iterations(); ++i)
            {
                results.push_back(benchmark(config));
            }

            auto write_path = generate_path(result_path, "single_thread_block_coder", config);
            assert(write_results(write_path, results) && "Error writing for config");
            std::cout << "Experiment end sleeping for 10 seconds" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(10));
        }
    }

}
}
