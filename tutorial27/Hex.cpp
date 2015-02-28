#include "Hex.h"
#include <QPointF>
#include <QPolygonF>
#include <QVector>
#include <QBrush>
#include "Game.h"

extern Game* game;

#include <QDebug> // TODO remove
Hex::Hex(QGraphicsItem *parent){
    // draw the polygon

    // points needed to draw hexagon: (1,0), (2,0), (3,1), (2,2), (1,2), (0,1)
    QVector<QPointF> hexPoints;
    hexPoints << QPointF(1,0) << QPointF(2,0) << QPointF(3,1) << QPointF(2,2)
              << QPointF(1,2) << QPointF(0,1);

    // scale the points
    int SCALE_BY = 40;
    for (size_t i = 0, n = hexPoints.size(); i < n; ++i){
        hexPoints[i] = hexPoints[i] * SCALE_BY;
    }

    // create a polygon with the scaled points
    QPolygonF hexagon(hexPoints);

    // draw the poly
    setPolygon(hexagon);

    // initialize
    isPlaced = false;
}

bool Hex::getIsPlaced(){
    return isPlaced;
}

QString Hex::getOwner(){
    return owner;
}

void Hex::mousePressEvent(QGraphicsSceneMouseEvent *event){
    // if this hex is NOT placed (so it is a card) then pick it up
    if (getIsPlaced() == false){
        game->pickUpCard(this);
    }

    // if this hex IS placed, then replace it
    else {
        game->placeCard(this);
    }
}

void Hex::setOwner(QString player){
    // set the owner
    owner = player;

    // change the color
    if (player == QString("NOONE")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::lightGray);
        setBrush(brush);
    }

    if (player == QString("PLAYER1")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::blue);
        setBrush(brush);
    }

    if (player == QString("PLAYER2")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::red);
        setBrush(brush);
    }
}

void Hex::setIsPlaced(bool b){
    isPlaced = b;
}
