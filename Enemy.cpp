#include "Enemy.h"
#include <QBrush>
#include <QTimer>
#include <cstdlib>
#include <ctime>
#include "Player.h"
#include "Map.h"

Enemy::Enemy(int gridX, int gridY, Map* map, Player* player) {
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

    if (canMove(direction)) {
        switch (direction) {
            case Direction::Left:
                setPos(x() - step, y());
                break;
            case Direction::Right:
                setPos(x() + step, y());
                break;
            case Direction::Up:
                setPos(x(), y() - step);
                break;
            case Direction::Down:
                setPos(x(), y() + step);
                break;
            default:
                break;
        }
    }

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

bool Enemy::canMove(Direction dir) {
    int newX = x();
    int newY = y();

    switch (dir) {
        case Direction::Left:
            newX -= step;
            break;
        case Direction::Right:
            newX += step;
            break;
        case Direction::Up:
            newY -= step;
            break;
        case Direction::Down:
            newY += step;
            break;
        default:
            return false;
    }

    int left = newX;
    int right = newX + Map::tileSize - 1;
    int top = newY;
    int bottom = newY + Map::tileSize - 1;

    return !(
        map->isWall(left / Map::tileSize, top / Map::tileSize) ||
        map->isWall(right / Map::tileSize, top / Map::tileSize) ||
        map->isWall(left / Map::tileSize, bottom / Map::tileSize) ||
        map->isWall(right / Map::tileSize, bottom / Map::tileSize)
    );
}

void Enemy::chooseNewDirection() {
    Direction dirs[] = {
        Direction::Up,
        Direction::Down,
        Direction::Left,
        Direction::Right
    };

    for (int i = 0; i < 4; i++) {
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
