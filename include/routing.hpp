#pragma once

#include "catalog.hpp"
#include <string>
#include <vector>

std::vector<std::string> fewestLayoverRoute(const std::string& origin, const std::string& destination,
                                            const std::vector<RouteEdge>& edges);
