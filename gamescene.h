#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <vector>

#include "player.h"
#include "mn

const int TILE_SIZE = 64; // Размер тайла в пикселях
const int GAME_WIDTH = 1400;
const int GAME_HEIGHT = 900;
const int ROWS = 10;
const int COLS = 20;

class GameScene : public QGraphicsScene {
    Q_OBJECT

public:
    GameScene(QObject* parent = nullptr) : QGraphicsScene(parent) {
        setSceneRect(0, 0, GAME_WIDTH, GAME_HEIGHT);
        createBackground();
        createPath();
    }

    void createPlayer(const QString& imagePath, int tileSize) {
        player1 = new Player(this, imagePath, tileSize);
    }

private:
    void createBackground() {
        QPixmap background("C:/Users/User/Desktop/Projects/ProgectQt/Progect/images/background.png");
        background = background.scaled(TILE_SIZE * COLS, TILE_SIZE * ROWS);
        addPixmap(background);
    }

    void createPath() {
        // Определяем фиксированный путь
        std::vector<std::vector<int>> path = {
            {2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3},
            {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 0, 1, 1, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 0},
            {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 5, 1, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 6, 1, 1, 5, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        };
    }

    void MainWindow::drawPath(QGraphicsScene *scene, const std::vector<std::vector<int>> &path)
    {
        QPixmap roadTile("C:/Users/User/Desktop/Projects/ProgectQt/Progect/images/road_tile.png");
        QPixmap startTile("C:/Users/User/Desktop/Projects/ProgectQt/Progect/images/start_tile.png");
        QPixmap finishTile("C:/Users/User/Desktop/Projects/ProgectQt/Progect/images/finish_tile.png");
        QPixmap trapTile("C:/Users/User/Desktop/Projects/ProgectQt/Progect/images/trap_tile.png");
        QPixmap boostTile("C:/Users/User/Desktop/Projects/ProgectQt/Progect/images/boost_tile.png");
        QPixmap extraTurnTile("C:/Users/User/Desktop/Projects/ProgectQt/Progect/images/extra_turn_tile.png");

        // Масштабируем тайлы до фиксированного размера
        roadTile = roadTile.scaled(TILE_SIZE, TILE_SIZE);
        startTile = startTile.scaled(TILE_SIZE, TILE_SIZE);
        finishTile = finishTile.scaled(TILE_SIZE, TILE_SIZE);
        trapTile = trapTile.scaled(TILE_SIZE, TILE_SIZE);
        boostTile = boostTile.scaled(TILE_SIZE, TILE_SIZE);
        extraTurnTile = extraTurnTile.scaled(TILE_SIZE, TILE_SIZE);

        int tileNumber = 0;

        for (int row = 0; row < path.size(); ++row)
        {
            for (int col = 0; col < path[row].size(); ++col)
            {
                QGraphicsPixmapItem *item = nullptr;
                if (path[row][col] == 2)
                {
                    item = scene->addPixmap(startTile);
                }
                else if (path[row][col] == 3)
                {
                    item = scene->addPixmap(finishTile);
                }
                else if (path[row][col] >= 4 && path[row][col] <= 6)
                {
                    if (path[row][col] == 4)
                        item = scene->addPixmap(trapTile);
                    else if (path[row][col] == 5)
                        item = scene->addPixmap(boostTile);
                    else if (path[row][col] == 6)
                        item = scene->addPixmap(extraTurnTile);
                }
                else if (path[row][col] != 0)
                {
                    item = scene->addPixmap(roadTile);
                }

                if (item)
                {
                    item->setPos(col * TILE_SIZE, row * TILE_SIZE);
                }
            }
        }
    }

private:
    Player* player1;
};

#endif // GAMESCENE_H
