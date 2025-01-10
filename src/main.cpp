#include <QApplication>
#include "ui/MainWindow.h"
#include "database/DatabaseManager.h"
#include <qmessagebox.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    try {
        // Initialisation de la base de données
        DatabaseManager* dbManager = DatabaseManager::getInstance();

        // Création et affichage de la fenêtre principale
        MainWindow mainWindow;
        mainWindow.show();

        return app.exec();
    }
    catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Erreur", 
            "Erreur lors du démarrage de l'application: " + QString(e.what()));
        return 1;
    }
}
