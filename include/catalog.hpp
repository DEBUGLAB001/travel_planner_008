#pragma once

#include <string>
#include <vector>

struct TripOption {
    std::string id;
    std::string origin;
    std::string destination;
    std::string origin_name;
    std::string destination_name;
    std::string departure;
    std::string arrival;
    std::string date;
    std::string airline;
    int duration_minutes;
    int price_cents;
    int seats_available;
    int stops;
};

struct RouteEdge {
    std::string from;
    std::string to;
    int duration_minutes;
    int price_cents;
};

const std::vector<TripOption>& tripCatalog();
const std::vector<RouteEdge>& routeCatalog();
