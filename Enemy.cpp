#include "Enemy.h"
#include <QBrush>
#include <QTimer>
#include <cstdlib>
#include <ctime>

#include "Player.h"

Enemy::Enemy(int gridX, int gridY, Map* map, Player* player) : MovingEntity(map, STEP) {
    this->map = map;
    this->player = player;
    this->step = STEP;
    this->alive = true;

    setRect(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT);
    setBrush(Qt::red);

    direction = Direction::Left;

    setPos(gridX * Map::tileSize, gridY * Map::tileSize);

    std::srand(std::time(nullptr));
}

void Enemy::advance(int phase) {
    if (!phase || !alive) return;

    if (!canMove(direction)) {
        chooseNewDirection();
    }

    setPosition(direction);

    if (collidesWithItem(player)) {
        if (player->isPowered()) {
            alive = false;
            setEnabled(false);
            setVisible(false);
        } else {
            player->dies();
        }
    }
}

void Enemy::chooseNewDirection() {
    Direction dirs[] = {
        Direction::Up,
        Direction::Down,
        Direction::Left,
        Direction::Right
    };

    while (true) {
        Direction d = dirs[rand() % 4];
        if (canMove(d)) {
            direction = d;
            return;
        }
    }

    direction = Direction::None;
}

void Enemy::setFrightened(bool frightened) {
    if (frightened) {
        setBrush(Qt::blue);
    } else {
        setBrush(Qt::red);
    }
}

bool Enemy::isAlive() const {
    return alive;
}
