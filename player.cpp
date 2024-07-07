#include "player.h"

Player::Player(QGraphicsScene *scene, const QString &imagePath, int tileSize)
    : tileSize(tileSize)
{
    QPixmap pixmap(imagePath);
    pixmap = pixmap.scaled(tileSize, tileSize);
    token = scene->addPixmap(pixmap);
    token->setPos(0, 0);
}

void Player::moveTo(int row, int col)
{
    token->setPos(col * tileSize, row * tileSize);
}
