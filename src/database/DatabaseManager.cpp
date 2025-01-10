#include "DatabaseManager.h"
#include <sstream>

bool DatabaseManager::addTrek(Trek& trek) {
    std::stringstream query;
    query << "INSERT INTO treks (nom, lieu, duree, prix, niveau, description) VALUES ('"
          << trek.getNom() << "', '"
          << trek.getLieu() << "', "
          << trek.getDuree() << ", "
          << trek.getPrix() << ", '"
          << trek.getNiveau() << "', '"
          << trek.getDescription() << "')";

    return mysql_query(connection, query.str().c_str()) == 0;
}

std::vector<Trek> DatabaseManager::getAllTreks() {
    std::vector<Trek> treks;
    if (mysql_query(connection, "SELECT * FROM treks") == 0) {
        MYSQL_RES* result = mysql_store_result(connection);
        MYSQL_ROW row;

        while ((row = mysql_fetch_row(result))) {
            Trek trek(row[1], row[2], std::stoi(row[3]), 
                     std::stod(row[4]), row[5], row[6]);
            trek.setId(std::stoi(row[0]));
            treks.push_back(trek);
        }

        mysql_free_result(result);
    }
    return treks;
}

bool DatabaseManager::addReservation(Reservation& reservation) {
    std::stringstream query;
    query << "INSERT INTO reservations (client_id, trek_id, date_reservation, statut) VALUES ("
          << reservation.getClientId() << ", "
          << reservation.getTrekId() << ", '"
          << reservation.getDateReservation() << "', '"
          << reservation.getStatut() << "')";

    return mysql_query(connection, query.str().c_str()) == 0;
}
