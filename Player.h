#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QKeyEvent>

#define PLAYER_WIDTH 30
#define PLAYER_HEIGHT 30
#define STEP 5
#define FRAME_TIME 16

class Map;
class Collectible;

enum class Direction {
    Up,
    Down,
    Left,
    Right,
    None
};

class Player : public QGraphicsRectItem {
public:
    Player(Map* map, QGraphicsTextItem* scoreText);

    void keyPressEvent(QKeyEvent* event) override;

    void advance(int phase) override;

    void collect(Collectible* collectible);

    bool isPowered() const;

    void dies();

private:
    Direction direction;
    Direction desiredDirection;
    int step;
    Map* map;
    int score;
    bool powerMode;
    int powerTimer;
    QGraphicsTextItem* scoreText;

    bool canMove(Direction dir);
};

#endif
