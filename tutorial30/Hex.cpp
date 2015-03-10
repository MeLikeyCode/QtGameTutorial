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

    // initialize side attacks to 0
    side0Attack = 0;
    side1Attack = 0;
    side2Attack = 0;
    side3Attack = 0;
    side4Attack = 0;
    side5Attack = 0;

    // create QGraphicsTextItems to represent visually each side's attack
    QGraphicsTextItem* text0 = new QGraphicsTextItem(QString::number(0),this);
    QGraphicsTextItem* text1 = new QGraphicsTextItem(QString::number(0),this);
    QGraphicsTextItem* text2 = new QGraphicsTextItem(QString::number(0),this);
    QGraphicsTextItem* text3 = new QGraphicsTextItem(QString::number(0),this);
    QGraphicsTextItem* text4 = new QGraphicsTextItem(QString::number(0),this);
    QGraphicsTextItem* text5 = new QGraphicsTextItem(QString::number(0),this);

    attackTexts.append(text0);
    attackTexts.append(text1);
    attackTexts.append(text2);
    attackTexts.append(text3);
    attackTexts.append(text4);
    attackTexts.append(text5);

    // set the correct position of the attack texts
    text0->setPos(50,0);
    text1->setPos(20,15);
    text2->setPos(20,40);
    text3->setPos(50,55);
    text4->setPos(80,40);
    text5->setPos(80,15);

    // make all attack texts invisible
    for (size_t i = 0, n = attackTexts.size(); i < n; i++){
        attackTexts[i]->setVisible(false);
    }
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

void Hex::setAttackOf(int side, int attack){
    // set the attack of the specified side (and update it's text)
    switch (side){
    case 0:
        side0Attack = attack;
        attackTexts[0]->setPlainText(QString::number(attack));
    case 1:
        side1Attack = attack;
        attackTexts[1]->setPlainText(QString::number(attack));
    case 2:
        side2Attack = attack;
        attackTexts[2]->setPlainText(QString::number(attack));
    case 3:
        side3Attack = attack;
        attackTexts[3]->setPlainText(QString::number(attack));
    case 4:
        side4Attack = attack;
        attackTexts[4]->setPlainText(QString::number(attack));
    case 5:
        side5Attack = attack;
        attackTexts[5]->setPlainText(QString::number(attack));
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

void Hex::displaySideAttacks(){
    // traverse through all the side_attack texts and make them visible
    for (size_t i = 0, n = attackTexts.size(); i < n; i++){
        attackTexts[i]->setVisible(true);
    }
}
