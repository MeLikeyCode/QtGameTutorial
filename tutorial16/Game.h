#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include "Tower.h"


class Game: public QGraphicsView{
    Q_OBJECT
public:
    // member functions
    Game();
    void setCursor(QString filename);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void createEnemies(int numberOfEnemies);
    void creatRoad();

    // member attributes
    QGraphicsScene * scene;
    QGraphicsPixmapItem * cursor;
    Tower * building;
    QTimer * spawnTimer;
    int enemiesSpawned;
    int maxNumberOfEnemies;
    QList<QPointF> pointsToFollow;
public slots:
    void spawnEnemy();
};

#endif // GAME_H
