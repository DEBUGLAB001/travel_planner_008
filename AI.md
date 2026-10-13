# Northstar Travel Planner — AI Context & Bug Reference

## 1. Project Overview

Northstar is a lightweight travel planning service written in C++14. It exposes an embedded HTTP server serving a single-page web application from `public/` along with REST endpoints for flight search, route planning, schedule window calculation, and in-memory reservations.

---

## 2. Repository Structure

```
travel-planner-cpp/
├── CMakeLists.txt         # CMake build configuration for library, server, and test runner
├── README.md              # Project documentation and challenge brief
├── AI.md                  # Architecture, bug catalog, and developer summary
├── challenge.json         # Platform challenge configuration and test commands
├── start.sh               # Bash live-reload server runner
├── include/
│   ├── travel.hpp         # Master domain header aggregating modular headers
│   ├── catalog.hpp        # Data structures (TripOption, RouteEdge) and catalog declarations
│   ├── search.hpp         # Departure search function declarations
│   ├── routing.hpp        # Connection layover planner declarations
│   ├── schedule.hpp       # Time window calendar declarations
│   ├── fare.hpp           # Cheapest route optimizer declarations
│   ├── pricing.hpp        # Group pricing calculation declarations
│   └── inventory.hpp      # Seat reservation inventory declarations
├── src/
│   ├── main.cpp           # Embedded HTTP server (WinSock2/POSIX) and REST routing
│   ├── catalog.cpp        # In-memory flight and route network fixtures
│   ├── search.cpp         # [BUG LOCATION] Departure search catalog filter
│   ├── routing.cpp        # [BUG LOCATION] Connection layover pathfinding
│   ├── schedule.cpp       # [BUG LOCATION] Calendar window interval merging
│   ├── fare.cpp           # [BUG LOCATION] Lowest fare route finder
│   ├── pricing.cpp        # [BUG LOCATION] Group ticket reservation pricing
│   └── inventory.cpp      # [BUG LOCATION] Seat capacity boundary checks
├── public/
│   ├── index.html         # Web frontend markup
│   ├── styles.css         # UI stylesheet
│   └── app.js             # Client application logic
└── tests/
    ├── test_runner.cpp    # Test suite executable and JSON telemetry reporter
    └── run_tests.sh       # Bash script to build and execute test suite
```

---

## 3. Bug Locations & Summary

The 6 challenge bugs are distributed across separate modular domain services in `src/`:
- **Bug 1:** [`src/search.cpp`](file:///c:/Users/prakh/Documents/Codex/2026-09-28/you-are-an-expert-application-engineer/outputs/travel-planner-cpp/src/search.cpp)
- **Bug 2:** [`src/routing.cpp`](file:///c:/Users/prakh/Documents/Codex/2026-09-28/you-are-an-expert-application-engineer/outputs/travel-planner-cpp/src/routing.cpp)
- **Bug 3:** [`src/schedule.cpp`](file:///c:/Users/prakh/Documents/Codex/2026-09-28/you-are-an-expert-application-engineer/outputs/travel-planner-cpp/src/schedule.cpp)
- **Bug 4:** [`src/fare.cpp`](file:///c:/Users/prakh/Documents/Codex/2026-09-28/you-are-an-expert-application-engineer/outputs/travel-planner-cpp/src/fare.cpp)
- **Bug 5:** [`src/pricing.cpp`](file:///c:/Users/prakh/Documents/Codex/2026-09-28/you-are-an-expert-application-engineer/outputs/travel-planner-cpp/src/pricing.cpp)
- **Bug 6:** [`src/inventory.cpp`](file:///c:/Users/prakh/Documents/Codex/2026-09-28/you-are-an-expert-application-engineer/outputs/travel-planner-cpp/src/inventory.cpp)

---

## 4. Detailed Bug Breakdown

### Bug 1: Departure Search Catalog Filter
- **File & Function:** `src/search.cpp` → `searchTrips()`
- **Issue:** Catalog entries are not pre-sorted by destination. Using `std::lower_bound` assumed sorted order, prematurely terminating the search and omitting valid matching flights.
- **Fix:** Iterate through the catalog linearly to collect all flights matching `origin`, `destination`, price threshold (`price_cents <= max_price_cents`), and available seats (`seats_available > 0`).

---

### Bug 2: Connection Planner Layover Minimization
- **File & Function:** `src/routing.cpp` → `fewestLayoverRoute()`
- **Issue:** Used depth-first search (DFS), which returned the first path explored rather than the path with the minimum number of flight legs/layovers.
- **Fix:** Implemented breadth-first search (BFS) with queue and parent tracking to guarantee discovering the path with the fewest hops.

---

### Bug 3: Flexible Windows Nested Booking Merge
- **File & Function:** `src/schedule.cpp` → `availableWindows()`
- **Issue:** When merging overlapping time intervals, assigning `merged.back().end_minute = end` caused nested intervals (which end earlier) to shrink the busy window rather than maintaining the maximum end boundary.
- **Fix:** Used `std::max(merged.back().end_minute, end)` when merging overlapping intervals.

---

### Bug 4: Fare Finder Lowest Total Price
- **File & Function:** `src/fare.cpp` → `cheapestRoute()`
- **Issue:** Used unweighted FIFO queue traversal (BFS), finding the connection with the fewest legs ($360) instead of the lowest cumulative ticket price ($270).
- **Fix:** Implemented a priority queue (min-heap ordered by total fare) to find the route with the minimum accumulated price.

---

### Bug 5: Group Pricing Reservation Total Scaling
- **File & Function:** `src/pricing.cpp` → `reservationTotalCents()`
- **Issue:** The traveler count was ignored (`(void)travelers;`), charging only for a single traveler regardless of party size.
- **Fix:** Multiplied single ticket price by party size: `trip.price_cents * travelers`.

---

### Bug 6: Seat Inventory Limit Boundary Check
- **File & Function:** `src/inventory.cpp` → `reserveSeats()`
- **Issue:** The check did not verify if `travelers > trip.seats_available`, allowing reservations to exceed remaining seats and decrementing availability into negative values.
- **Fix:** Added a boundary guard `if (travelers < 1 || travelers > trip.seats_available) return false;` without modifying inventory.
