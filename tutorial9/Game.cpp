#include "Game.h"
#include <QGraphicsScene>
#include "Tower.h"

Game::Game(){
    // create a scene
    scene = new QGraphicsScene(this);

    // set the scene
    setScene(scene);

    // create a tower
    Tower * t = new Tower();

    // add the tower to scene
    scene->addItem(t);

    setFixedSize(800,600);
}
