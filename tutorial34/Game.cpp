#include "Game.h"
#include "HexBoard.h"
#include "Button.h"
#include <QGraphicsTextItem>
#include <stdlib.h> // srand() and rand()
#include <time.h> // time()

#include <QDebug>
Game::Game(QWidget *parent){
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,768);

    // set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1024,768);
    setScene(scene);

}

void Game::start(){
    // initialize
    cardToPlace = NULL;
    numCardsPlaced = 0;

    // clear the screen
    scene->clear();

    // test code TODO remove
    hexBoard = new HexBoard();
    hexBoard->placeHexes(200,30,7,7);
    drawGUI();
    createInitialCards();
}

void Game::restartGame(){
    // clear some stuff then call start()
    player1Cards.clear();
    player2Cards.clear();
    hexBoard->getHexes().clear();
    scene->clear();
    start();
}

void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity){
    // draws a panel at the specified location with the specified properties
    QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}

void Game::drawGUI(){
    // draw the left panel
    drawPanel(0,0,150,768,Qt::darkCyan,1);

    // draw the right panel
    drawPanel(874,0,150,768,Qt::darkCyan,1);

    // place player 1 text
    QGraphicsTextItem* p1 = new QGraphicsTextItem("Player 1's Cards: ");
    p1->setPos(25,0);
    scene->addItem(p1);

    // place player 1 text
    QGraphicsTextItem* p2 = new QGraphicsTextItem("Player 2's Cards: ");
    p2->setPos(874+25,0);
    scene->addItem(p2);

    // place whosTurnText
    whosTurnText = new QGraphicsTextItem();
    setWhosTurn(QString("PLAYER1"));
    whosTurnText->setPos(490,0);
    scene->addItem(whosTurnText);

}

void Game::createNewCard(QString player){
    // create the card
    Hex* card = new Hex();
    card->setOwner(player);
    card->setIsPlaced(false);

    // randommize side attacks of card
    for (size_t i = 0, n = 6; i < n; i++){
        // generate a random number
        int randNum = rand() % 6 + 1; // 1 - 6
        card->setAttackOf(i,randNum);
    }

    // make side attacks visible
    card->displaySideAttacks();

    // add the card to the proper list
    if (player == QString("PLAYER1")){
        player1Cards.append(card);
    }
    else {
        player2Cards.append(card);
    }

    // draw the cards
    drawCards();
}

void Game::createInitialCards(){
    // create player 1's cards
    for (size_t i = 0, n = 5; i < n; i++){
        createNewCard(QString("PLAYER1"));
    }

    // create player 2's cards
    for (size_t i = 0, n = 5; i < n; i++){
        createNewCard(QString("PLAYER2"));
    }

    drawCards();
}

void Game::drawCards(){
    // traverse through list of cards and draw them

    // remove all of player1's cards from the scene
    for (size_t i = 0, n = player1Cards.size(); i < n; i++){
        scene->removeItem(player1Cards[i]);
    }
    // remove all of player2's cards from the scene
    for (size_t i = 0, n = player2Cards.size(); i < n; i++){
        scene->removeItem(player2Cards[i]);
    }

    // draw player1's cards
    for (size_t i = 0, n = player1Cards.size(); i < n; i++){
        Hex* card = player1Cards[i];
        card->setPos(13,25+85*i);
        scene->addItem(card);
    }

    // draw player2's cards
    for (size_t i = 0, n = player2Cards.size(); i < n; i++){
        Hex* card = player2Cards[i];
        card->setPos(874+13,25+85*i);
        scene->addItem(card);
    }
}

void Game::displayMainMenu(){
    // create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Hex Warz"));
    QFont titleFont("comic sans",50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // create the play button
    Button* playButton = new Button(QString("Play"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(playButton);

    // create the quit button
    Button* quitButton = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);
}

QString Game::getWhosTurn(){
    return whosTurn_;
}

void Game::setWhosTurn(QString player){
    // change the QString
    whosTurn_ = player;

    // change the QGraphicsTextItem
    whosTurnText->setPlainText(QString("Whos turn: ") + player);
}

void Game::pickUpCard(Hex *card){
    // picks up the specified card
    if (card->getOwner() == getWhosTurn() && cardToPlace == NULL){
        cardToPlace = card;
        originalPos = card->pos();
        return;
}
}

void Game::placeCard(Hex *hexToReplace){
    // replaces the specified hex with the cardToPlace
    cardToPlace->setPos(hexToReplace->pos());
    hexBoard->getHexes().removeAll(hexToReplace);
    hexBoard->getHexes().append(cardToPlace);
    scene->removeItem(hexToReplace);
    cardToPlace->setIsPlaced(true);
    removeFromDeck(cardToPlace,getWhosTurn());

    //find neighbors
    cardToPlace->findNeighbors();
    cardToPlace->captureNeighbors();

    // make card to place null
    cardToPlace = NULL;

    // replace the placed card w a new one
    createNewCard(getWhosTurn());

    // make it the next players turn
    nextPlayersTurn();

    numCardsPlaced++;

    if (numCardsPlaced >= hexBoard->getHexes().size()){
        gameOver();
    }
}

void Game::nextPlayersTurn(){
    if (getWhosTurn() == QString("PLAYER1")){
        setWhosTurn(QString("PLAYER2"));
    }
    else {
        setWhosTurn(QString("PLAYER1"));
    }
}

void Game::removeFromDeck(Hex *card, QString player){
    if (player == QString("PLAYER1")){
        // remove from player 1
        player1Cards.removeAll(card);
    }

    if (player == QString("PLAYER2")){
        // remove from player 1
        player2Cards.removeAll(card);
    }

}

void Game::gameOver(){
    // count hexes, determine who has more, set messege
    int p1hexes = 0;
    int p2hexes = 0;
    for (size_t i = 0, n = hexBoard->getHexes().size(); i < n; ++i){
        if (hexBoard->getHexes()[i]->getOwner() == QString("PLAYER1")){
            p1hexes++;
        }
        else if (hexBoard->getHexes()[i]->getOwner() == QString("PLAYER2")){
            p2hexes++;
        }
    }

    QString messege;
    if (p1hexes > p2hexes){
        messege = "Player 1 has won!";
    }
    else if (p2hexes > p1hexes){
        messege = "Player 2 has won!";
    }
    else {
        messege = "Tie game!";
    }

    displayGameOverWindow(messege);

    }

void Game::displayGameOverWindow(QString textToDisplay){
    // disable all scene items
    for (size_t i = 0, n = scene->items().size(); i < n; i++){
        scene->items()[i]->setEnabled(false);
    }

    // pop up semi transparent panel
    drawPanel(0,0,1024,768,Qt::black,0.65);

    // draw panel
    drawPanel(312,184,400,400,Qt::lightGray,0.75);

    // create playAgain button
    Button* playAgain = new Button(QString("Play Again"));
    playAgain->setPos(410,300);
    scene->addItem(playAgain);
    connect(playAgain,SIGNAL(clicked()),this,SLOT(restartGame()));

    // create quit button
    Button* quit = new Button(QString("Quit"));
    quit->setPos(410,375);
    scene->addItem(quit);
    connect(quit,SIGNAL(clicked()),this,SLOT(close()));

    // create text annoucning winner
    QGraphicsTextItem* overText = new QGraphicsTextItem(textToDisplay);
    overText->setPos(460,225);
    scene->addItem(overText);

}

void Game::mouseMoveEvent(QMouseEvent *event){
    // if there is a cardToPlace, then make it follow the mouse
    if (cardToPlace){
        cardToPlace->setPos(event->pos());
    }

    QGraphicsView::mouseMoveEvent(event);
}

void Game::mousePressEvent(QMouseEvent *event){
    // make right click return cardToPlace to originalPos
    if (event->button() == Qt::RightButton){
        if (cardToPlace){
            cardToPlace->setPos(originalPos);
            cardToPlace = NULL;
            return;
        }
    }

    QGraphicsView::mousePressEvent(event);
}
