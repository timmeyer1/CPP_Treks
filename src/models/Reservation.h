#pragma once
#include <string>
#include "Client.h"
#include "Trek.h"

class Reservation {
private:
    int id;
    int clientId;
    int trekId;
    std::string dateReservation;
    std::string statut;

public:
    Reservation(int clientId, int trekId);

    // Getters
    int getId() const { return id; }
    int getClientId() const { return clientId; }
    int getTrekId() const { return trekId; }
    std::string getDateReservation() const { return dateReservation; }
    std::string getStatut() const { return statut; }

    // Setters
    void setId(int newId) { id = newId; }
    void setStatut(const std::string& newStatut) { statut = newStatut; }
};
