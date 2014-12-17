#include <QApplication>
#include "Game.h"

/*
Tutorial topics:
Review/use a bunch of previously learned concepts
New Topics:
-QLineF::angle()
*/

Game * game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();
    game->show();

    return a.exec();
}
