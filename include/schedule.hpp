#pragma once

#include <vector>

struct TimeWindow {
    int start_minute;
    int end_minute;
};

std::vector<TimeWindow> availableWindows(int day_start, int day_end, std::vector<TimeWindow> booked);
