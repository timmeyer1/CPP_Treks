#include "DatabaseManager.h"
#include <stdexcept>
#include <iostream>
#include <sstream>

DatabaseManager* DatabaseManager::instance = nullptr;

DatabaseManager::DatabaseManager() {
    if (!connect()) {
        throw std::runtime_error("Échec de connexion à la base de données");
    }
}

bool DatabaseManager::connect() {
    connection = mysql_init(nullptr);
    if (!connection) {
        return false;
    }

    if (!mysql_real_connect(connection, "localhost", "root", "admin",
                            "trek_manager", 0, nullptr, 0)) {
        std::cerr << "Erreur MySQL: " << mysql_error(connection) << std::endl;
        return false;
    }
    return true;
}

DatabaseManager* DatabaseManager::getInstance() {
    if (instance == nullptr) {
        instance = new DatabaseManager();
    }
    return instance;
}

DatabaseManager::~DatabaseManager() {
    if (connection) {
        mysql_close(connection);
    }
}

// Implémentation des méthodes CRUD pour Client
bool DatabaseManager::addClient(Client& client) {
    std::string query = "INSERT INTO clients (nom, prenom, email, telephone) "
                        "VALUES ('" + client.getNom() + "', '" + 
                        client.getPrenom() + "', '" +
                        client.getEmail() + "', '" + 
                        client.getTelephone() + "')";
    
    return mysql_query(connection, query.c_str()) == 0;
}

std::vector<Client> DatabaseManager::getAllClients() {
    std::vector<Client> clients;
    if (mysql_query(connection, "SELECT * FROM clients") == 0) {
        MYSQL_RES* result = mysql_store_result(connection);
        if (result) {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result))) {
                Client client(
                    row[1] ? row[1] : "",  // nom
                    row[2] ? row[2] : "",  // prenom
                    row[3] ? row[3] : "",  // email
                    row[4] ? row[4] : ""   // telephone
                );
                client.setId(std::stoi(row[0]));
                clients.push_back(client);
            }
            mysql_free_result(result);
        }
    }
    return clients;
}

// Implémentation des méthodes CRUD pour Trek
bool DatabaseManager::addTrek(Trek& trek) {
    std::stringstream query;
    query << "INSERT INTO treks (nom, lieu, duree, prix, niveau, description) VALUES ('"
          << trek.getNom() << "', '"
          << trek.getLieu() << "', "
          << trek.getDuree() << ", "
          << trek.getPrix() << ", '"
          << trek.getNiveau() << "', '"
          << trek.getDescription() << "')";

    if (mysql_query(connection, query.str().c_str()) == 0) {
        trek.setId(mysql_insert_id(connection));
        return true;
    }
    return false;
}

// Implémentation des méthodes CRUD pour Réservations
bool DatabaseManager::addReservation(Reservation& reservation) {
    std::stringstream query;s
    query << "INSERT INTO reservations (client_id, trek_id, date_reservation, statut) VALUES ("
          << reservation.getClientId() << ", "
          << reservation.getTrekId() << ", '"
          << reservation.getDateReservation() << "', '"
          << reservation.getStatut() << "')";

    if (mysql_query(connection, query.str().c_str()) == 0) {
        reservation.setId(mysql_insert_id(connection));
        return true;
    }
    return false;
}


std::vector<Trek> DatabaseManager::getAllTreks() {
    std::vector<Trek> treks;
    if (mysql_query(connection, "SELECT * FROM treks") == 0) {
        MYSQL_RES* result = mysql_store_result(connection);
        if (result) {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result))) {
                Trek trek(
                    row[1] ? row[1] : "",  // nom
                    row[2] ? row[2] : "",  // lieu
                    std::stoi(row[3] ? row[3] : "0"),  // duree
                    std::stod(row[4] ? row[4] : "0"),  // prix
                    row[5] ? row[5] : "",  // niveau
                    row[6] ? row[6] : ""   // description
                );
                trek.setId(std::stoi(row[0]));
                treks.push_back(trek);
            }
            mysql_free_result(result);
        }
    }
    return treks;
}
