#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "HexBoard.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    // constructors
    Game(QWidget* parent=NULL);

    // public methods
    void displayMainMenu();
    QString getWhosTurn();
    void setWhosTurn(QString player);

    // public attributes
    QGraphicsScene* scene;
    HexBoard* hexBoard;

public slots:
    void start();

private:
    // private methods
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    void drawGUI();
    void createNewCard(QString player);
    void createInitialCards();
    void drawCards();

    // private attributes
    QString whosTurn_;
    QGraphicsTextItem* whosTurnText;
    QList<Hex* > player1Cards;
    QList<Hex* > player2Cards;
};

#endif // GAME_H
