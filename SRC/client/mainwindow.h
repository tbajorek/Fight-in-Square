#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QHostAddress>
#include <QRegularExpression>
#include <QtAlgorithms>
#include <QTableWidget>
#include "../config.h"
#include "canvas.h"
#include "Game.h"
#include "NetworkManager.h"
#include "help.h"

namespace Ui {
    class MainWindow;
}

/**
 * @brief
 * Główne okno aplikacji
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

public slots:

    /**
     * @brief
     * Slot, który łapie sygnał zmiany stanu aplikacji
     * wysyłany przez klasę Game.
     * Dzięki temu główne okno wie, kiedy przełączyć
     * się na tryb wyświetlania menu/gry,
     * wie kiedy zmienić nazwy przycisków itd...
     * @param gameStatus nowy stan gry
     */
    void onGameStatusChanged(Game::STATUS gameStatus);

    /**
     * @brief onErrorCodeChanged
     * @param errCode kod błędu
     */
    void onErrorCodeChanged(int errCode);

    /**
     * @brief
     * Slot na sygnał aktualizacji modelu w klasie Game.
     * Gdy odebrany zostanie sygnał, zmienia się np.
     * tabela toplisty, ilość życia gracza itd...
     */
    void onModelActualized();

private slots:

    /**
     * @brief
     * Slot na kliknięcie przycisku "Połącz" bądź
     * "Rozłącz" w menu głównym.
     */
    void on_connectButton_clicked();

    /**
     * @brief
     * Slot na wciśnięcie przycisku "Pomoc"
     * w menu głównym.
     */
    void on_helpButton_clicked();

    /**
     * @brief
     * Slot na wciśnięcie przycisku "Zakończ"
     * w menu głównym.
     */
    void on_exitButton_clicked();

    /**
     * @brief
     * Slot, który obsługuje przycisk
     * rozłączenia się z grą, gdy gracz
     * jest w trakcie gry.
     */
    void on_exitGameButton_clicked();

    /**
     * @brief on_exitGameOverButton_clicked
     * Slot do obsługi naciśniętego przycisku
     * powrotu do menu głównego z ekranu
     * game over
     */
    void on_exitGameOverButton_clicked();

private:

    /**
     * @brief
     * Obsługa zdarzenia wciśnięcia klawisza.
     * @param e
     * Obiekt zdarzenia
     */
    void keyPressEvent(QKeyEvent *e);

    /**
     * @brief
     * Obsługa zdarzenia puszczenia klawisza.
     * @param e
     * Obiekt zdarzenia
     */
    void keyReleaseEvent(QKeyEvent *e);

    /**
     * @brief fillInTable Wypełnia tabelę
     * @param table Widget tabeli do wypełnienia
     */
    void fillInTable(QTableWidget *table);

    Ui::MainWindow *ui;

    /**
     * @brief game Obiekt gry
     */
    Game game;

    /**
     * @brief canvas Obiekk do rysowania po nim
     */
    Canvas canvas;

    /**
     * @brief networkManager Manager połączenia
     */
    NetworkManager networkManager;
    bool updated;
    Help *help;

};

#endif // MAINWINDOW_H
