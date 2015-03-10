#ifndef HEX_H
#define HEX_H

#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>

class Hex: public QGraphicsPolygonItem{
public:
    // constructors
    Hex(QGraphicsItem* parent=NULL);
    // getters
    int getAttackOf(int side);
    bool getIsPlaced();
    QString getOwner();

    // event
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    // setters
    void setAttackOf(int side, int attack);
    void setOwner(QString player);
    void setIsPlaced(bool b);

    void displaySideAttacks();

private:
    bool isPlaced;
    QString owner;
    int side0Attack;
    int side1Attack;
    int side2Attack;
    int side3Attack;
    int side4Attack;
    int side5Attack;
    QList<QGraphicsTextItem*> attackTexts;
};

#endif // HEX_H
