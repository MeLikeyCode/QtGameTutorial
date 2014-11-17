#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>

#include <QDebug>
Bullet::Bullet(){
    // drew the rect
    setRect(0,0,10,50);

    // connect
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);
}

void Bullet::move(){
    // move bullet up
    setPos(x(),y()-10);
    if (pos().y() + rect().height() < 0){
        scene()->removeItem(this);
        delete this;
    }
}
