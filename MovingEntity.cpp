#include "MovingEntity.h"

MovingEntity::MovingEntity(Map* map, int step) : map(map), step(step) {
}

bool MovingEntity::canMove(Direction dir) {
    int newX = x();
    int newY = y();

    switch (dir) {
        case Direction::Left:  newX -= step; break;
        case Direction::Right: newX += step; break;
        case Direction::Up:    newY -= step; break;
        case Direction::Down:  newY += step; break;
        default: return false;
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

void MovingEntity::setPosition(Direction direction) {
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
            case Direction::None:
                break;
        }
    }
}
