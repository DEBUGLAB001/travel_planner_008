#include "inventory.hpp"

bool reserveSeats(TripOption& trip, int travelers) {
    if (travelers < 1) {
        return false;
    }

    trip.seats_available -= travelers;
    return true;
}
