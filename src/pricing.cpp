#include "pricing.hpp"

int reservationTotalCents(const TripOption& trip, int travelers) {
    (void)travelers;
    return trip.price_cents;
}
