#ifndef BROWNTOWER_H
#define BROWNTOWER_H

#include "Tower.h"

class BrownTower: public Tower{
    Q_OBJECT
public:
    BrownTower(QGraphicsItem * parent=0);
    void fire();
public slots:
    void aquire_target();
};

#endif // BROWNTOWER_H
