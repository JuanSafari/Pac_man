#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <vector>
#include "Collectible.h"

#define MAP_WIDTH 20
#define MAP_HEIGHT 20
#define TILE_SIZE 30

class Collectible;

class Map {
public:
    static const int width = MAP_WIDTH;
    static const int height = MAP_HEIGHT;
    static const int tileSize = TILE_SIZE;

    Map();

    void draw(QGraphicsScene* scene);

    void addSimpleCollectible(int gridX, int gridY);

    void addSpecialCollectible(int gridX, int gridY);

    void removeCollectible(Collectible* collectible);

    bool isWall(int gridX, int gridY) const;

    void getPlayerStart(int& x, int& y) const;

private:
    int tiles[height][width];
    std::vector<Collectible *> collectibles;
    int playerStartX;
    int playerStartY;
};


#endif //MAP_H
