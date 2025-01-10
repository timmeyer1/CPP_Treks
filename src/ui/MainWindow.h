#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include "../database/DatabaseManager.h"
#include "../api/WeatherAPI.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onClientAdded();
    void onTrekAdded();
    void onReservationAdded();
    void updateWeatherInfo();

private:
    QTabWidget* tabWidget;
    DatabaseManager* dbManager;
    WeatherAPI* weatherApi;

    // Widgets pour le formulaire client
    QLineEdit* nomInput;
    QLineEdit* prenomInput;
    QLineEdit* emailInput;
    QLineEdit* telephoneInput;

    // Widgets pour le formulaire trek
    QLineEdit* trekNomInput;
    QLineEdit* trekLieuInput;
    QLineEdit* trekPrixInput;
    QComboBox* trekNiveauCombo;
    QLineEdit* trekDureeInput;
    QLineEdit* trekDescriptionInput;

    void setupUi();
    void createClientsTab();
    void createTreksTab();
    void createReservationsTab();
    void connectSignals();
};

#endif // MAINWINDOW_H
