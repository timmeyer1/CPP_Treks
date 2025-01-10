#pragma once
#include <mysql/mysql.h>
#include <string>
#include <vector>
#include "../models/Client.h"
#include "../models/Trek.h"
#include "../models/Reservation.h"

class DatabaseManager {
private:
    MYSQL* connection;
    static DatabaseManager* instance;
    
    DatabaseManager();
    bool connect();

public:
    static DatabaseManager* getInstance();
    ~DatabaseManager();

    // Méthodes Clients
    bool addClient(Client& client);
    bool updateClient(const Client& client);
    bool deleteClient(int clientId);
    std::vector<Client> getAllClients();
    Client* getClientById(int id);

    // Méthodes Treks
    bool addTrek(Trek& trek);
    bool updateTrek(const Trek& trek);
    bool deleteTrek(int trekId);
    std::vector<Trek> getAllTreks();
    std::vector<Trek> getTreksByDifficulty(const std::string& niveau);

    // Méthodes Réservations
    bool addReservation(Reservation& reservation);
    bool updateReservationStatus(int reservationId, const std::string& status);
    std::vector<Reservation> getReservationsByClient(int clientId);
};
