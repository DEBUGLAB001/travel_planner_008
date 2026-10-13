#include "search.hpp"
#include <algorithm>

std::vector<TripOption> searchTrips(const std::string& origin, const std::string& destination, int max_price_cents) {
    const auto& trips = tripCatalog();
    std::vector<TripOption> matches;

    auto first = std::lower_bound(trips.begin(), trips.end(), destination,
        [](const TripOption& trip, const std::string& code) {
            return trip.destination < code;
        });

    for (auto it = first; it != trips.end() && it->destination == destination; ++it) {
        if (it->origin == origin && it->price_cents <= max_price_cents && it->seats_available > 0) {
            matches.push_back(*it);
        }
    }

    return matches;
}
