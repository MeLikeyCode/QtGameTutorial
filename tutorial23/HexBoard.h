#ifndef HEXBOARD_H
#define HEXBOARD_H

#include <QList>
#include "Hex.h"

class HexBoard{
public:
    // constructors
    HexBoard();

    // getters/setters
    QList<Hex*> getHexes();

    // public methods
    void placeHexes(int x, int y, int cols, int rows);

private:
    void createHexColumn(int x, int y, int numOfRows);
    QList<Hex*> hexes;
};

#endif // HEXBOARD_H
