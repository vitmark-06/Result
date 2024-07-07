#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class Player {

public:
    Player(QGraphicsScene *scene, const QString &imagePath, int tileSize);
    void moveTo(int row, int col);
    void setName(const QString& name);

private:
    QGraphicsPixmapItem *token;
    int tileSize;
    QString name;
};

#endif // PLAYER_H
