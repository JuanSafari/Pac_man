#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>

#include "MovingEntity.h"

class Enemy : public MovingEntity {
public:
    Enemy(int gridX, int gridY, Map* map, Player* player);

    void advance(int phase) override;

    void setFrightened(bool frightened);

    bool isAlive() const;

private:
    Map* map;
    Player* player;

    Direction direction;
    int step;

    bool alive;

    void chooseNewDirection();
};


#endif //ENEMY_H
