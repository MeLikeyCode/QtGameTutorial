#include "BuildTowerIcon.h"
#include "Game.h"

extern Game * game;

BuildTowerIcon::BuildTowerIcon(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    setPixmap(QPixmap(":/images/towericon.png"));
}

void BuildTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (!game->build){
        game->build = new Tower();
        game->setCursor(QString(":/images/tower.png"));
    }
}
