#include <QApplication>
#include "Game.h"

/*
Tutorial Topics:
-resource files
-QMediaPlayer, setMedia(), QUrl, play()
*/

Game * game;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    game = new Game();
    game->show();

    return a.exec();
}
