#include "BuildRedTowerIcon.h"
#include "Game.h"
#include "BrownTower.h"
#include "RedTower.h"

extern Game * game;

BuildRedTowerIcon::BuildRedTowerIcon(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    setPixmap(QPixmap(":/images/redtowericon.png"));
}

void BuildRedTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent* event){
    if (!game->building){
        game->building = new RedTower();
        game->setCursor(QString(":/images/redtower.png"));
    }
}

