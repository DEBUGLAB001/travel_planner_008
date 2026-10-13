#pragma once

#include "catalog.hpp"
#include <string>
#include <vector>

struct RouteResult {
    std::vector<std::string> airports;
    int total_minutes;
    int total_price_cents;
};

RouteResult cheapestRoute(const std::string& origin, const std::string& destination,
                          const std::vector<RouteEdge>& edges);
