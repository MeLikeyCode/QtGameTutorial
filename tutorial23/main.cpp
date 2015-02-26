#include <QApplication>
#include "Game.h"

/*
Goal of tutorial:
-implement Button class
-make starting Menu
*/

Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();
    game->show();
    game->displayMainMenu();

    return a.exec();
}
