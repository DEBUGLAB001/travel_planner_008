#include "routing.hpp"
#include <functional>
#include <set>

std::vector<std::string> fewestLayoverRoute(const std::string& origin, const std::string& destination,
                                            const std::vector<RouteEdge>& edges) {
    std::set<std::string> visiting;
    std::vector<std::string> path(1, origin);

    std::function<bool(const std::string&)> visit = [&](const std::string& city) {
        if (city == destination) {
            return true;
        }

        visiting.insert(city);

        for (const auto& edge : edges) {
            if (edge.from == city && !visiting.count(edge.to)) {
                path.push_back(edge.to);
                if (visit(edge.to)) {
                    return true;
                }
                path.pop_back();
            }
        }

        return false;
    };

    if (!visit(origin)) {
        return {};
    }

    return path;
}
