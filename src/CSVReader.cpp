#include<fstream>
#include<string>
#include<iostream>
#include<sstream>
#include<vector>

#define MAX_ROW 1000
#define MAX_COLUMN 100
using namespace std;

void readCSV(const std::string& filename, vector<vector<string>>& data) {
    ifstream file_stream(filename);
    string line;

    if (!file_stream.is_open()) {
        cerr << "Could not open file: " << filename << endl;
        return;
    }

    while (getline(file_stream, line)) {
        stringstream ss(line);
        string cell;
        vector<string> row;
        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        data.push_back(row);

    }
    file_stream.close();
}

int main() {
    std::string filename = "../data/tick_by_tick_data.csv"; // Replace with your CSV file path
    std::vector<std::vector<std::string>> data;

    readCSV(filename, data);

    // Output the data for verification
    for (const auto& row : data) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}