#include "Collectible.h"
#include <QBrush>
#include <QGraphicsScene>

Collectible::Collectible(int x, int y, int size, CollectibleType type)
    : QGraphicsEllipseItem(x, y, size, size), type(type) {
    if (type == CollectibleType::Simple) {
        value = 10;
        setBrush(Qt::yellow);
    } else {
        value = 50;
        setBrush(Qt::red);
    }
}

void Collectible::draw(QGraphicsScene* scene) {
    scene->addItem(this);
}

CollectibleType Collectible::getType() const {
    return type;
}

int Collectible::getValue() const {
    return value;
}
