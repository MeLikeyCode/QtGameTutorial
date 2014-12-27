#include <QApplication>
#include "Game.h"

/*
Tutorial topics:
Review/apply a bunch of previously learned concepts
New Topic:
QPen, QBrush, setPen(), setBrush()
*/

Game * game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();
    game->show();

    return a.exec();
}
