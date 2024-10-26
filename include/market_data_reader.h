// market_data_reader.h
#pragma once
#include <vector>
#include <string>

class market_data_reader {
public:
    virtual ~market_data_reader() = default;
    
    // Pure virtual functions that derived classes must implement
    virtual bool read_file(const std::string& filename) = 0;
    virtual std::vector<std::string> get_headers() const = 0;
    virtual std::vector<std::vector<std::string>> get_data() const = 0;
    virtual bool validate() const = 0;
};
