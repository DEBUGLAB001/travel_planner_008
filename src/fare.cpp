#include "fare.hpp"
#include <algorithm>
#include <map>
#include <queue>
#include <set>

RouteResult cheapestRoute(const std::string& origin, const std::string& destination,
                          const std::vector<RouteEdge>& edges) {
    std::queue<std::string> pending;
    std::map<std::string, std::string> parent;
    std::map<std::string, int> duration;
    std::map<std::string, int> fare;
    std::set<std::string> visited;

    pending.push(origin);
    visited.insert(origin);
    duration[origin] = 0;
    fare[origin] = 0;

    while (!pending.empty()) {
        const std::string city = pending.front();
        pending.pop();

        if (city == destination) {
            break;
        }

        for (const auto& edge : edges) {
            if (edge.from == city && !visited.count(edge.to)) {
                visited.insert(edge.to);
                parent[edge.to] = city;
                duration[edge.to] = duration[city] + edge.duration_minutes;
                fare[edge.to] = fare[city] + edge.price_cents;
                pending.push(edge.to);
            }
        }
    }

    if (origin != destination && !visited.count(destination)) {
        return {{}, 0, 0};
    }

    std::vector<std::string> path;
    for (std::string city = destination; !city.empty(); city = parent[city]) {
        path.push_back(city);
        if (city == origin) {
            break;
        }
    }

    std::reverse(path.begin(), path.end());
    return {path, duration[destination], fare[destination]};
}
