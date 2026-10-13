#include "catalog.hpp"

const std::vector<TripOption>& tripCatalog() {
    static const std::vector<TripOption> trips = {
        {"NS-204", "NYC", "BOS", "New York", "Boston", "08:10", "09:28", "2026-10-14", "Northstar Air", 78, 16900, 6, 0},
        {"NS-318", "NYC", "SFO", "New York", "San Francisco", "09:40", "13:05", "2026-10-14", "Northstar Air", 385, 38900, 3, 0},
        {"NS-411", "NYC", "LAX", "New York", "Los Angeles", "10:15", "13:42", "2026-10-14", "Pacific Line", 387, 32900, 8, 0},
        {"NS-322", "NYC", "SFO", "New York", "San Francisco", "12:20", "15:51", "2026-10-14", "Pacific Line", 391, 33900, 4, 0},
        {"NS-522", "NYC", "MIA", "New York", "Miami", "11:05", "14:20", "2026-10-14", "Coast & Air", 375, 22900, 2, 0},
        {"NS-610", "BOS", "SFO", "Boston", "San Francisco", "14:15", "18:10", "2026-10-14", "Northstar Air", 415, 29900, 5, 0},
        {"NS-710", "NYC", "SEA", "New York", "Seattle", "16:30", "20:12", "2026-10-14", "Pacific Line", 402, 35900, 7, 0},
        {"NS-329", "NYC", "SFO", "New York", "San Francisco", "18:50", "22:21", "2026-10-14", "Northstar Air", 391, 41900, 1, 0}
    };
    return trips;
}

const std::vector<RouteEdge>& routeCatalog() {
    static const std::vector<RouteEdge> edges = {
        {"SEA", "DEN", 145, 8000}, {"DEN", "DFW", 115, 10000}, {"DFW", "NYC", 195, 9000},
        {"SEA", "SFO", 125, 22000}, {"SFO", "NYC", 335, 14000}, {"SEA", "LAX", 165, 12500},
        {"LAX", "NYC", 300, 15000}, {"DEN", "ORD", 150, 11000}, {"ORD", "NYC", 120, 8000}
    };
    return edges;
}
