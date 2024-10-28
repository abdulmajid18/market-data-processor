#include "../include/circular_buffer.h"
#include "../include/market_data_types.h"

int main() {
    CircularBuffer<MarketDataTypes::CompositeMarketData> data_buffer(3);

    MarketDataTypes::Level1Data level1_data = {
        "AAPL",
        MarketDataTypes::TimePoint::parse("2024-10-27 09:30:00"), // Example timestamp
        150.0, 100,
        151.0, 50,
        150.5, 75,
        MarketDataTypes::TimePoint::parse("2024-10-27 09:30:01") // Last trade timestamp
    };

    MarketDataTypes::Level2Data level2_data = {
        "AAPL",
        MarketDataTypes::TimePoint::parse("2024-10-27 09:30:00"), // Example timestamp
        {
            MarketDataTypes::Level2Data::PriceLevel{149.5, 100}, 
            MarketDataTypes::Level2Data::PriceLevel{149.0, 150},
            MarketDataTypes::Level2Data::PriceLevel{148.5, 200}
        },  // Bids
        {
            MarketDataTypes::Level2Data::PriceLevel{151.5, 100}, 
            MarketDataTypes::Level2Data::PriceLevel{152.0, 50},
            MarketDataTypes::Level2Data::PriceLevel{152.5, 75}
        }   // Asks
    };

    MarketDataTypes::Level3Data level3_data = {
        "AAPL",
        MarketDataTypes::TimePoint::parse("2024-10-27 09:30:01"), // Example timestamp
        150.5, 75
    };

    MarketDataTypes::CompositeMarketData composite_data = {level1_data, level2_data, level3_data};

    data_buffer.enqueue(composite_data);
    // do your analysis or processing
    auto data = data_buffer.dequeue();
};