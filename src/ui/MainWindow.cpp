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
    QWidget* treksWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(treksWidget);

    // Groupe formulaire pour nouveau trek
    QGroupBox* formGroup = new QGroupBox("Nouveau Trek");
    QFormLayout* formLayout = new QFormLayout();

    // Création des champs
    trekNomInput = new QLineEdit();
    trekLieuInput = new QLineEdit();
    trekDureeInput = new QLineEdit();
    trekPrixInput = new QLineEdit();
    trekNiveauCombo = new QComboBox();
    trekDescriptionInput = new QLineEdit();

    // Ajout des niveaux de difficulté
    trekNiveauCombo->addItem("Facile");
    trekNiveauCombo->addItem("Moyen");
    trekNiveauCombo->addItem("Difficile");
    trekNiveauCombo->addItem("Expert");

    // Ajout des champs au formulaire
    formLayout->addRow("Nom:", trekNomInput);
    formLayout->addRow("Lieu:", trekLieuInput);
    formLayout->addRow("Durée (jours):", trekDureeInput);
    formLayout->addRow("Prix:", trekPrixInput);
    formLayout->addRow("Niveau:", trekNiveauCombo);
    formLayout->addRow("Description:", trekDescriptionInput);

    QPushButton* addButton = new QPushButton("Ajouter Trek");
    formLayout->addRow(addButton);

    formGroup->setLayout(formLayout);
    layout->addWidget(formGroup);

    // Ajout de l'onglet
    tabWidget->addTab(treksWidget, "Treks");

    connect(addButton, &QPushButton::clicked, this, &MainWindow::onTrekAdded);
}

void MainWindow::onTrekAdded()
{
    try {
        Trek trek(
            trekNomInput->text().toStdString(),
            trekLieuInput->text().toStdString(),
            trekDureeInput->text().toInt(),
            trekPrixInput->text().toDouble(),
            trekNiveauCombo->currentText().toStdString(),
            trekDescriptionInput->text().toStdString()
        );

        if (dbManager->addTrek(trek)) {
            QMessageBox::information(this, "Succès", "Trek ajouté avec succès!");
            // Réinitialisation des champs
            trekNomInput->clear();
            trekLieuInput->clear();
            trekDureeInput->clear();
            trekPrixInput->clear();
            trekDescriptionInput->clear();
            trekNiveauCombo->setCurrentIndex(0);
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de l'ajout du trek");
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Erreur", e.what());
    }
}

void MainWindow::createReservationsTab()
{
    QWidget* reservationsWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(reservationsWidget);

    // Groupe formulaire pour nouvelle réservation
    QGroupBox* formGroup = new QGroupBox("Nouvelle Réservation");
    QFormLayout* formLayout = new QFormLayout();

    // Création des combobox pour sélection client et trek
    QComboBox* clientCombo = new QComboBox();
    QComboBox* trekCombo = new QComboBox();

    // Remplissage des combobox avec les données de la base
    auto clients = dbManager->getAllClients();
    for (const auto& client : clients) {
        clientCombo->addItem(QString::fromStdString(client.getNom() + " " + client.getPrenom()), 
                            QVariant(client.getId()));
    }

    auto treks = dbManager->getAllTreks();
    for (const auto& trek : treks) {
        trekCombo->addItem(QString::fromStdString(trek.getNom()), 
                          QVariant(trek.getId()));
    }

    formLayout->addRow("Client:", clientCombo);
    formLayout->addRow("Trek:", trekCombo);

    QPushButton* addButton = new QPushButton("Créer Réservation");
    formLayout->addRow(addButton);

    formGroup->setLayout(formLayout);
    layout->addWidget(formGroup);

    // Ajout de l'onglet
    tabWidget->addTab(reservationsWidget, "Réservations");

    connect(addButton, &QPushButton::clicked, [=]() {
        int clientId = clientCombo->currentData().toInt();
        int trekId = trekCombo->currentData().toInt();
        
        Reservation reservation(clientId, trekId);
        
        if (dbManager->addReservation(reservation)) {
            QMessageBox::information(this, "Succès", "Réservation créée avec succès!");
            clientCombo->setCurrentIndex(0);
            trekCombo->setCurrentIndex(0);
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de la création de la réservation");
        }
    });
}

void MainWindow::onReservationAdded() {
    // Exemple : afficher un message ou connecter des fonctionnalités à venir
    QMessageBox::information(this, "Info", "Réservation ajoutée (fonctionnalité à compléter).");
}