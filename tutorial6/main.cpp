#include <QApplication>
#include "Game.h"

/*
Tutorial Topics:
-parents
-QGraphicsTextItem, setPlainText(), setFont(),setDefaultTextColor()
*/

Game * game;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    game = new Game();
    game->show();

    return a.exec();
}
