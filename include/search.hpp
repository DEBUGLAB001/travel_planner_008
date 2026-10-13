#pragma once

#include "catalog.hpp"
#include <string>
#include <vector>

std::vector<TripOption> searchTrips(const std::string& origin, const std::string& destination, int max_price_cents);
