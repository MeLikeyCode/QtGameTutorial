#include "BuildBrownTowerIcon.h"
#include "Game.h"
#include "BrownTower.h"

extern Game * game;

BuildBrownTowerIcon::BuildBrownTowerIcon(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    setPixmap(QPixmap(":/images/browntowericon.png"));
}

void BuildBrownTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent* event){
    if (!game->building){
        game->building = new BrownTower();
        game->setCursor(QString(":/images/browntower.png"));
    }
}
