#include "Reservation.h"
#include <ctime>

Reservation::Reservation(int clientId, int trekId)
    : clientId(clientId), trekId(trekId) {
    time_t now = time(nullptr);
    dateReservation = ctime(&now);
    statut = "En attente";
}
