#include "Player.h"
#include "Map.h"
#include "Collectible.h"
#include <QBrush>
#include <QTimer>

Player::Player(Map* map, QGraphicsTextItem* scoreText) {
    setRect(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT);
    setBrush(Qt::yellow);
    setFlag(QGraphicsItem::ItemIsFocusable);
    this->direction = Direction::None;
    this->desiredDirection = Direction::None;
    this->step = STEP;
    this->map = map;
    this->score = 0;
    this->scoreText = scoreText;
    this->powerMode = false;
    this->powerTimer = 0;

    int startX, startY;
    map->getPlayerStart(startX, startY);
    setPos(startX, startY);
}

void Player::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Left) {
        desiredDirection = Direction::Left;
    } else if (event->key() == Qt::Key_Right) {
        desiredDirection = Direction::Right;
    } else if (event->key() == Qt::Key_Up) {
        desiredDirection = Direction::Up;
    } else if (event->key() == Qt::Key_Down) {
        desiredDirection = Direction::Down;
    }
    update();
}

bool Player::canMove(Direction dir) {
    int newX = x();
    int newY = y();

    switch (dir) {
        case Direction::Left: newX -= step;
            break;
        case Direction::Right: newX += step;
            break;
        case Direction::Up: newY -= step;
            break;
        case Direction::Down: newY += step;
            break;
        default: return false;
    }

    int left = newX;
    int right = newX + Map::tileSize - 1;
    int top = newY;
    int bottom = newY + Map::tileSize - 1;

    int leftCol = left / Map::tileSize;
    int rightCol = right / Map::tileSize;
    int topRow = top / Map::tileSize;
    int bottomRow = bottom / Map::tileSize;

    return !(
        map->isWall(leftCol, topRow) ||
        map->isWall(rightCol, topRow) ||
        map->isWall(leftCol, bottomRow) ||
        map->isWall(rightCol, bottomRow)
    );
}


void Player::advance(int phase) {
    if (!phase) return;

    if (desiredDirection != direction && canMove(desiredDirection)) {
        direction = desiredDirection;
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
            case Direction::None:
                break;
        }
    }

    for (QGraphicsItem* item: collidingItems()) {
        if (auto* c = dynamic_cast<Collectible *>(item)) {
            collect(c);
        }
    }

    if (powerMode) {
        powerTimer -= FRAME_TIME;
        if (powerTimer <= 0) {
            powerMode = false;
            powerTimer = 0;
        }
    }
}

void Player::collect(Collectible* collectible) {
    score += collectible->getValue();

    scoreText->setPlainText("Score: " + QString::number(score));

    if (collectible->getType() == CollectibleType::Special) {
        powerMode = true;
        powerTimer = 5000;
    }

    scene()->removeItem(collectible);
    map->removeCollectible(collectible);

    collectible->setEnabled(false);
    collectible->setVisible(false);

    QTimer::singleShot(0, [collectible]() {
        delete collectible;
    });
}

bool Player::isPowered() const {
    return powerMode;
}

void Player::dies() {
    setEnabled(false);
    setVisible(false);
}
