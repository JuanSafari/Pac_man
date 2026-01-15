#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>

#define POS_X 5
#define POS_Y 5

class Map;
class Player;
enum class Direction;

class Enemy : public QGraphicsRectItem {
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

    bool canMove(Direction dir);

    void chooseNewDirection();
};


#endif //ENEMY_H
