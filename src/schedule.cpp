#include "schedule.hpp"
#include <algorithm>

std::vector<TimeWindow> availableWindows(int day_start, int day_end, std::vector<TimeWindow> booked) {
    std::sort(booked.begin(), booked.end(), [](const TimeWindow& a, const TimeWindow& b) {
        return a.start_minute < b.start_minute;
    });

    std::vector<TimeWindow> merged;

    for (const auto& window : booked) {
        if (window.end_minute <= day_start || window.start_minute >= day_end) {
            continue;
        }

        const int start = std::max(day_start, window.start_minute);
        const int end = std::min(day_end, window.end_minute);

        if (merged.empty() || start > merged.back().end_minute) {
            merged.push_back({start, end});
        } else {
            merged.back().end_minute = end;
        }
    }

    std::vector<TimeWindow> free;
    int cursor = day_start;

    for (const auto& window : merged) {
        if (window.start_minute > cursor) {
            free.push_back({cursor, window.start_minute});
        }
        cursor = std::max(cursor, window.end_minute);
    }

    if (cursor < day_end) {
        free.push_back({cursor, day_end});
    }

    return free;
}
