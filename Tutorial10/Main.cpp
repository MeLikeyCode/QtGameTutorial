#include <QApplication>
#include "Game.h"

/*
Tutorial topics:
Review:
-QObject, Q_OBJECT macro, signals and slots
-setSceneRect()
-turning off scrollbars
New Topics:
-mousePressEvent, QMouseEvent
-qmath.h qSin, qCos, qDegreesToRadians and qRadiansToDegrees
*/

Game * game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();
    game->show();

    return a.exec();
}
