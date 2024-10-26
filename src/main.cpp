// main.cpp
#include "../include/csv_reader.h"
#include <iostream>
#include <memory>

int main() {
    try {
        // Using CSV Reader
        std::unique_ptr<market_data_reader> reader = std::make_unique<csv_reader>(',', true);
        if (!reader->read_file("../data/level_2_data.csv")) {
            std::cerr << "Failed to read CSV file" << std::endl;
            return 1;
        }

        if (!reader->validate()) {
            std::cerr << "CSV data validation failed!" << std::endl;
            return 1;
        }

        // Print headers
        auto headers = reader->get_headers();
        std::cout << "Headers: ";
        for (const auto& header : headers) {
            std::cout << header << " ";
        }
        std::cout << std::endl;

        // Print data
        auto data = reader->get_data();
        for (size_t i = 0; i < data.size(); ++i) {
            std::cout << "Row " << i + 1 << ": ";
            for (const auto& cell : data[i]) {
                std::cout << cell << " ";
            }
            std::cout << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}