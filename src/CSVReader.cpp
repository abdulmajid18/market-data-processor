#include<fstream>
#include<string>
#include<iostream>
#include<sstream>
#include<vector>

#define MAX_ROW 1000
#define MAX_COLUMN 100
using namespace std;

class CSVReader{
    private:
        char delimiter;
        bool hasHeader;
        std::vector<string> headers;

        static std::string trim(const std::string& str) {
            const std::string whitespace = " \t\r\n";
            size_t start = str.find_first_not_of(whitespace);
            size_t end = str.find_last_not_of(whitespace);

            if (start == std::string::npos) return "";
            return str.substr(start, end - start + 1);
        }

    public:
        CSVReader(char delim = ',', bool header = true)
        : delimiter(delim), hasHeader(header) {}

        std::vector<std::vector<std::string>> readCSV(const std::string& filename) {
            std::vector<std::vector<std::string>> data;
            std::ifstream file(filename);

            if (!file.is_open()) {
                throw std::runtime_error("Could not open file: " + filename);
            }

            std::string line;
            bool firstLine = true;

            while (std::getline(file, line)) {
                if (line.empty())
                    continue;
                
                std::vector<std::string> row;
                std::string cell;
                std::stringstream cellStream(line);

                while (std::getline(cellStream, cell, delimiter)) {
                    row.push_back(trim(cell));
                }

                if (firstLine && hasHeader) {
                    headers = row;
                    firstLine = false;
                }

                data.push_back(row);
            }
            file.close();
            return data;
        }

        const std::vector<std::string>& getHeaders() const {
            return headers;
        }

        bool validateData(const std::vector<std::vector<std::string>>& data) const {
            if (data.empty()) return true;

            size_t expectedCols = hasHeader ? headers.size() : data[0].size();

            for (size_t i = 0; i < data.size(); ++i) {
                if (data[i].size() != expectedCols) {
                    std::cerr << "Row " << i + 1 << " has incorrect number of columns. "
                         << "Expected: " << expectedCols << ", Got: " << data[i].size() << std::endl;
                return false;
                }
            }
            return true;
        }

};


int main() {
    try {
        std::string filename = "../data/level_2_data.csv"; 
        CSVReader reader(',', true);

        auto data = reader.readCSV(filename);

        if (!reader.validateData(data)) {
            std::cerr << "CSV data validation failed!" << std::endl;
            return 1;
        }

        const auto& headers = reader.getHeaders();
        if (!headers.empty()) {
                std::cout << "Headers: ";
                for (const auto& header : headers) {
                    std::cout << header << " ";
                }
                std::cout << std::endl << std::endl;
        };

        std::cout << "Data:" << std::endl;
        for (size_t i = 0; i < data.size(); ++i) {
            std::cout << "Row " << i + 1 << ": ";
            for (const auto& cell : data[i]) {
                std::cout << cell << " ";
            }
            std::cout << std::endl;
        };
    }  catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}