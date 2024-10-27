#ifndef MARKET_DATA_TYPES_H
#define MARKET_DATA_TYPES_H

#include <vector>
#include <string>
#include<chrono>
#include<optional>
#include<variant>

namespace MarketDataTypes {
    struct TimePoint {
        std::chrono::system_clock::time_point timestamp;

        static TimePoint parse(const std::string& ts);
    };

    struct Level1Data {
        std::string symbol;
        TimePoint timestamp;
        double bid_price;
        int bid_size;
        double ask_price;
        int ask_size;
        double last_trade_price;
        int last_trade_size;
        TimePoint last_trade_timestamp;
    };

    struct Level2Data {
        static const int DEPTH = 3;  // Number of price levels

        std::string symbol;
        TimePoint timestamp;
        struct PriceLevel {
            double price;
            int size;
        };
        std::array<PriceLevel, DEPTH> bids;
        std::array<PriceLevel, DEPTH> asks;
    };

    struct Level3Data {
        std::string symbol;
        TimePoint timestamp;
        double trade_price;
        int trade_size;
    };

    using MarketData = std::variant<Level1Data, Level2Data, Level3Data>;
}

#endif