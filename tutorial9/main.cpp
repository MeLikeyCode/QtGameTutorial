#include <QApplication>
#include "Game.h"

/*
Tutorial topics:
Review:
-QGraphicsScene, QGraphicsItem, QGraphicsView (and their distinct coordinate systems)
-Parenthood (when parent object get deleted, so do their children, but not vice versa)
-etc...
New Topics:
-QPoint, QLine, QRect, QPolygon
-QVector
*/


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game * game = new Game();
    game->show();

    return a.exec();
}
