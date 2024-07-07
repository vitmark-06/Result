#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <ctime>
#include <vector>
#include <cstdlib>
#include <algorithm>

#include <QAction>
#include <QApplication>
#include <QDateTime>
#include <QDir>
#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include <QRandomGenerator>
#include <QGridLayout>

#include "player.h"
#include "mainmenuwidget.h"

const int TILE_SIZE = 64;
const int GAME_WIDTH = 1400;
const int GAME_HEIGHT = 900;
const int ROWS = 10;
const int COLS = 20;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void drawPath(QGraphicsScene *scene, const std::vector<std::vector<int>> &path);
    void updateSettings(int numPlayers, const QVector<QString>& playerNames);
    void createMenu();
    void movePlayer(int numTiles);

    QGraphicsScene *scene;
    QGraphicsView* view;
    QGraphicsPixmapItem* figureItem1;
    QGraphicsPixmapItem* figureItem2;

    Player *player1;
    Player *player2;
    Player *player3;

    QMenuBar* menuBar;
    QMenu* gameMenu;
    QAction* newGameAction;
    QAction* rulesAction;
    QAction* aboutAction;
    QAction* saveResultsAction;
    QAction* helpAction;
    QAction* exitAction;

    MainMenuWidget* mainMenu;
    QLabel* diceLabel;
    QLabel* currentPlayerLabel;
    QPushButton* exitButton;

    QVector<QString> playerNames;
    int numPlayers;
    int currentPlayer = 1;
    int diceRoll = 0;
    bool canMove = false;

    int startX;
    int startY;
    QString winnerName = "Player 1";

    QVector<QPoint> luckyTiles = { QPoint(2, 4), QPoint(6, 5), QPoint(11, 2), QPoint(15, 7), QPoint(17, 2) };
    QVector<QPoint> unluckyTiles = { QPoint(1, 5), QPoint(10, 2), QPoint(12, 7), QPoint(15, 4), QPoint(17, 5), QPoint(19, 8) };

protected:
    void mousePressEvent(QMouseEvent* event) override;

private slots:
    void startNewGame();
    void newGame();
    void gameRules();
    void aboutGame();
    void saveResults();
    void help();
    void exitGame();

    void rollDice();
    void setCurrentPlayer(const QString& playerName);
};

#endif // MAINWINDOW_H
