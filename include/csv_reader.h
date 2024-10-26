// csv_reader.h

#pragma once
#include "market_data_reader.h"
#include<fstream>
#include<sstream>

class csv_reader: public market_data_reader {
    private:
        char delimiter;
        bool has_header;
        std::vector<std::string> headers;
        std::vector<std::vector<std::string>> data;

        static std::string trim(const std::string& str);
    public:
        csv_reader(char delim = ',', bool header = true);
        
        // Implementing interface methods
        bool read_file(const std::string& filename) override;
        std::vector<std::string> get_headers() const override;
        std::vector<std::vector<std::string>> get_data() const override;
        bool validate() const override;
};