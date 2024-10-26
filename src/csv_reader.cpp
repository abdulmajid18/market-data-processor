// csv_reader.cpp
#include "../include/csv_reader.h"
#include <stdexcept>

csv_reader::csv_reader(char delim, bool header) 
    : delimiter(delim), has_header(header) {}

std::string csv_reader::trim(const std::string& str) {
    const std::string whitespace = " \t\r\n";
    size_t start = str.find_first_not_of(whitespace);
    size_t end = str.find_last_not_of(whitespace);
    
    if (start == std::string::npos) return "";
    return str.substr(start, end - start + 1);
}

bool csv_reader::read_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    data.clear();
    headers.clear();
    
    std::string line;
    bool firstLine = true;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::vector<std::string> row;
        std::string cell;
        std::stringstream cellStream(line);

        while (std::getline(cellStream, cell, delimiter)) {
            row.push_back(trim(cell));
        }

        if (firstLine && has_header) {
            headers = row;
            firstLine = false;
            continue;
        }
        data.push_back(row);
    }

    file.close();
    return true;
}

std::vector<std::string> csv_reader::get_headers() const {
    return headers;
}

std::vector<std::vector<std::string>> csv_reader::get_data() const {
    return data;
}

bool csv_reader::validate() const {
    if (data.empty()) return true;
    
    size_t expectedCols = has_header ? headers.size() : data[0].size();
    
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i].size() != expectedCols) {
            return false;
        }
    }
    return true;
}