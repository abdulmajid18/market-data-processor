#include "../include/market_data_types.h"
#include<vector>
#include<string>

using namespace MarketDataTypes;

class MarketDataParser {
    public:
     static MarketData parse_row(const std::vector<std::string>& row, int level) {
        switch(level) {
            case 1:
                return parse_level1(row);
            case 2:
                return parse_level2(row);
            case 3:
                return parse_level3(row);
            default:
                throw std::runtime_error("Unknown market data level");
        }
    }

    private:
        static Level1Data parse_level1(const std::vector<std::string>& row) {
             Level1Data data;
            return data;
        }

        static Level2Data parse_level2(const std::vector<std::string>& row) {
            Level2Data data;
            return data;
        }
        
        static Level3Data parse_level3(const std::vector<std::string>& row) {
            Level3Data data;
            return data;
        }
};