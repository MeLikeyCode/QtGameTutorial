#include "GreenTower.h"
#include <QTimer>
#include "Bullet.h"
#include "Game.h"

extern Game * game;

GreenTower::GreenTower(QGraphicsItem *parent){
    // connect a timer to aquire_target
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(aquire_target()));
    timer->start(1000);
}

void GreenTower::fire(){
    // create the bullets
    Bullet * bullet1 = new Bullet();
    Bullet * bullet2 = new Bullet();
    Bullet * bullet3 = new Bullet();

    // set the graphics
    bullet1->setPixmap(QPixmap(":/images/greentowerbullet.png"));
    bullet2->setPixmap(QPixmap(":/images/greentowerbullet.png"));
    bullet3->setPixmap(QPixmap(":/images/greentowerbullet.png"));

    bullet1->setPos(x()+44,y()+44);
    bullet2->setPos(x()+44,y()+44);
    bullet3->setPos(x()+44,y()+44);

    QLineF ln(QPointF(x()+44,y()+44),attack_dest);
    int angle = -1 * ln.angle();

    bullet1->setRotation(angle);
    bullet2->setRotation(angle+10);
    bullet3->setRotation(angle-10);

    game->scene->addItem(bullet1);
    game->scene->addItem(bullet2);
    game->scene->addItem(bullet3);
}

void GreenTower::aquire_target(){
    Tower::aquire_target();
}

