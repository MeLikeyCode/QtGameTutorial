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


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game * game = new Game();
    game->show();

    return a.exec();
}
