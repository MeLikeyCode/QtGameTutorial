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

    // create lines
    createLines();

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

int Hex::getAttackOf(int side){
    if (side == 0){
        return side0Attack;
    }
    else if (side == 1){
        return side1Attack;
    }
    else if (side == 2){
        return side2Attack;
    }
    else if (side == 3){
        return side3Attack;
    }
    else if (side == 4){
        return side4Attack;
    }
    else if (side == 5){
        return side5Attack;
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

void Hex::createLines(){
    QPointF hexCenter(x()+60,y()+40);
    QPointF finalPt(hexCenter.x(),hexCenter.y()-65);
    QLineF ln(hexCenter,finalPt);

    for (size_t i = 0, n = 6; i < n; ++i){
        QLineF lnCopy(ln);
        lnCopy.setAngle(90+60*i);
        QGraphicsLineItem* line = new QGraphicsLineItem(lnCopy,this);
        lines.append(line);
        line->setVisible(false);
    }
}

void Hex::findNeighbors(){
    for (size_t i = 0, n = lines.size(); i < n; i++){
        // if the line collides with an item of type Hex, add it to neighbors
        QList<QGraphicsItem*> cItems = lines[i]->collidingItems();
        for (size_t j = 0; j < cItems.size(); j++){
            Hex* item = dynamic_cast<Hex*>(cItems[j]);
            if (cItems[j] != this && item){
                neighbors.append(item);
            }
        }
    }
}

void Hex::switchOwner(){
    // if the owner is player1, make it player two and vice versa
    if (getOwner() == QString("PLAYER1")){
        setOwner(QString("PLAYER2"));
    }
    else if (getOwner() == QString("PLAYER2")){
        setOwner(QString("PLAYER1"));
    }
}

void Hex::captureNeighbors(){
    // traverses through neighbors, captures weaker neighbors
    for (size_t i = 0, n = neighbors.size(); i < n; i++){
        bool isEnemy = false;
        bool isNotNeutral = false;

        if (this->getOwner() != neighbors[i]->getOwner()){
            isEnemy = true;
        }

        if (neighbors[i]->owner != QString("NOONE")){
            isNotNeutral = true;
        }

        // it is an enemy and not neutral
        if (isEnemy && isNotNeutral){
            // find attack of touching sides
            int thisAttack = 0;
            int neighborsAttack = 0;
            if (i == 0){
                thisAttack = getAttackOf(0);
                neighborsAttack = neighbors[0]->getAttackOf(3);
            }
            else if (i == 1){
                thisAttack = getAttackOf(1);
                neighborsAttack = neighbors[1]->getAttackOf(4);
            }
            else if (i == 2){
                thisAttack = getAttackOf(2);
                neighborsAttack = neighbors[2]->getAttackOf(5);
            }
            else if (i == 3){
                thisAttack = getAttackOf(3);
                neighborsAttack = neighbors[3]->getAttackOf(0);
            }
            else if (i == 4){
                thisAttack = getAttackOf(4);
                neighborsAttack = neighbors[4]->getAttackOf(1);
            }
            else if (i == 5){
                thisAttack = getAttackOf(5);
                neighborsAttack = neighbors[5]->getAttackOf(2);
            }

            // if this has greater attack, switch neighbors owner
            if (thisAttack > neighborsAttack){
                neighbors[i]->switchOwner();
            }

        }
    }
}
