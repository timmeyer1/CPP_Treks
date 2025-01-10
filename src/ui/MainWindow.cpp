#include "MainWindow.h"
#include <QMessageBox>
#include <QFormLayout>
#include <QGroupBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , weatherApi(new WeatherAPI("votre_clé_api_ici"))
{
    dbManager = DatabaseManager::getInstance();
    setupUi();
    connectSignals();
    updateWeatherInfo();
}

MainWindow::~MainWindow()
{
    delete weatherApi;
}

void MainWindow::setupUi()
{
    setWindowTitle("Gestionnaire de Treks");
    setMinimumSize(800, 600);

    // Widget central
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Layout principal
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // TabWidget
    tabWidget = new QTabWidget(this);
    mainLayout->addWidget(tabWidget);

    // Création des onglets
    createClientsTab();
    createTreksTab();
    createReservationsTab();
}

void MainWindow::createClientsTab()
{
    QWidget* clientsWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(clientsWidget);

    // Groupe formulaire
    QGroupBox* formGroup = new QGroupBox("Nouveau Client");
    QFormLayout* formLayout = new QFormLayout();

    // Champs de saisie
    nomInput = new QLineEdit();
    prenomInput = new QLineEdit();
    emailInput = new QLineEdit();
    telephoneInput = new QLineEdit();

    formLayout->addRow("Nom:", nomInput);
    formLayout->addRow("Prénom:", prenomInput);
    formLayout->addRow("Email:", emailInput);
    formLayout->addRow("Téléphone:", telephoneInput);

    QPushButton* addButton = new QPushButton("Ajouter Client");
    formLayout->addRow(addButton);

    formGroup->setLayout(formLayout);
    layout->addWidget(formGroup);

    tabWidget->addTab(clientsWidget, "Clients");

    connect(addButton, &QPushButton::clicked, this, &MainWindow::onClientAdded);
}

void MainWindow::onClientAdded()
{
    try {
        Client client(
            nomInput->text().toStdString(),
            prenomInput->text().toStdString(),
            emailInput->text().toStdString(),
            telephoneInput->text().toStdString()
        );

        if (dbManager->addClient(client)) {
            QMessageBox::information(this, "Succès", "Client ajouté avec succès!");
            nomInput->clear();
            prenomInput->clear();
            emailInput->clear();
            telephoneInput->clear();
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de l'ajout du client");
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Erreur", e.what());
    }
}

void MainWindow::connectSignals()
{
    // Les connexions seront ajoutées lors de l'implémentation des autres fonctionnalités
}

void MainWindow::updateWeatherInfo()
{
    try {
        WeatherAPI::WeatherData weather = weatherApi->getWeatherByCoordinates(48.8566, 2.3522);
        // À compléter avec l'affichage des données météo
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Erreur Météo", 
            "Impossible de récupérer les informations météo: " + QString(e.what()));
    }
}

void MainWindow::createTreksTab()
{
    // À implémenter
}

void MainWindow::createReservationsTab()
{
    // À implémenter
}
