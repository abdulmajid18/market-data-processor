#include<string>
#include<chrono>
#include<variant>
#include<sstream>

struct TimePoint {
    std::chrono::system_clock::time_point timestamp;

    static TimePoint parse(const std::string& ts) {
        std::tm tm = {};
        std::istringstream ss(ts);
        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
        if (ss.fail()) {
            throw std::invalid_argument("Invalid time format");
        }
        auto time_t = std::mktime(&tm);
        TimePoint tp;
        tp.timestamp = std::chrono::system_clock::from_time_t(time_t);
        return tp;
    }
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