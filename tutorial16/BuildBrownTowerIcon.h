#ifndef BUILDBROWNTOWERICON_H
#define BUILDBROWNTOWERICON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class BuildBrownTowerIcon: public QGraphicsPixmapItem{
public:
    BuildBrownTowerIcon(QGraphicsItem* parent=0);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
};

#endif // BUILDBROWNTOWERICON_H
