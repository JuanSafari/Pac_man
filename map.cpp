#include "map.h"
#include "Player.h"
#include "Collectible.h"
#include "Enemy.h"
#include <QBrush>

Map::Map() {
    int temp[20][20] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1},
        {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1},
        {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            tiles[i][j] = temp[i][j];

    playerStartX = 1 * tileSize;
    playerStartY = 1 * tileSize;
}

void Map::draw(QGraphicsScene* scene) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (tiles[i][j] == 1) {
                QGraphicsRectItem* wall = new QGraphicsRectItem(j * tileSize, i * tileSize, tileSize, tileSize);
                wall->setBrush(Qt::blue);
                wall->setPen(Qt::NoPen);
                scene->addItem(wall);
            }
        }
    }

    for (Collectible* collectible: collectibles) {
        if (collectible) {
            collectible->draw(scene);
        }
    }
}


void Map::addSimpleCollectible(int gridX, int gridY) {
    int collectibleSize = 10;
    int x = gridX * tileSize + tileSize / 2 - collectibleSize / 2;
    int y = gridY * tileSize + tileSize / 2 - collectibleSize / 2;
    Collectible* c = new Collectible(x, y, collectibleSize, CollectibleType::Simple);
    collectibles.push_back(c);
}

void Map::addSpecialCollectible(int gridX, int gridY) {
    int collectibleSize = 15;
    int x = gridX * tileSize + tileSize / 2 - collectibleSize / 2;
    int y = gridY * tileSize + tileSize / 2 - collectibleSize / 2;
    Collectible* c = new Collectible(x, y, collectibleSize, CollectibleType::Special);
    collectibles.push_back(c);
}

void Map::removeCollectible(Collectible* collectible) {
    auto it = std::find(collectibles.begin(), collectibles.end(), collectible);
    if (it != collectibles.end()) {
        collectibles.erase(it);
    }
}

void Map::addEnemy(int gridX, int gridY, Player* player) {
    Enemy* enemy = new Enemy(gridX, gridY, this, player);
    enemies.push_back(enemy);
}

std::vector<Enemy*>& Map::getEnemies() {
    return enemies;
}

bool Map::isWall(int gridX, int gridY) const {
    if (gridX < 0 || gridX >= width || gridY < 0 || gridY >= height) {
        return true;
    }
    return tiles[gridY][gridX] == 1;
}

void Map::getPlayerStart(int& x, int& y) const {
    x = playerStartX;
    y = playerStartY;
}
