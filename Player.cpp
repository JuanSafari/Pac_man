#include "Player.h"
#include <QBrush>
#include <QTimer>

Player::Player(Map* map, QGraphicsTextItem* scoreText): MovingEntity(map, STEP) {
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

void Player::advance(int phase) {
    if (!phase) return;

    if (desiredDirection != direction && canMove(desiredDirection)) {
        direction = desiredDirection;
    }

    setPosition(direction);

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
