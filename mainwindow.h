#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <ctime>
#include <vector>
#include <cstdlib>
#include <algorithm>

#include <QAction>
#include <QApplication>
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

    QGraphicsScene *scene;
    QGraphicsView* view;
    QGraphicsPixmapItem* figureItem;

    Player *player1;
    Player *player2;
    Player *player3;

    QMenuBar* menuBar;
    QMenu* gameMenu;
    QAction* newGameAction;
    QAction* rulesAction;
    QAction* aboutAction;
    QAction* saveResultsAction;
    QAction* exitAction;

    MainMenuWidget* mainMenu;
    QLabel* currentPlayerLabel;
    QPushButton* exitButton;

    QVector<QString> playerNames;
    int numPlayers;
    int currentPlayer;

    int startX;
    int startY;

    void movePlayer(int numTiles);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private slots:
    void startNewGame();
    void gameRules();
    void aboutGame();
    void saveResults();
    void exitGame();

    void rollDice();
    void setCurrentPlayer(const QString& playerName);
};

#endif // MAINWINDOW_H
