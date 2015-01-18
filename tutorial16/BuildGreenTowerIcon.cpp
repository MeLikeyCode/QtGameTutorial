
#include "BuildGreenTowerIcon.h"
#include "Game.h"
#include "GreenTower.h"

extern Game * game;

BuildGreenTowerIcon::BuildGreenTowerIcon(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    setPixmap(QPixmap(":/images/greentowericon.png"));
}

void BuildGreenTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent* event){
    if (!game->building){
        game->building = new GreenTower();
        game->setCursor(QString(":/images/greentower.png"));
    }
}
