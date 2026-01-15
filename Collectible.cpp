#include "Collectible.h"
#include <QBrush>
#include <QGraphicsScene>

Collectible::Collectible(int x, int y, int size, CollectibleType type)
    : QGraphicsEllipseItem(x, y, size, size), type(type) {
    if (type == CollectibleType::Simple) {
        value = NORMAL_VALUE;
        setBrush(Qt::yellow);
    } else {
        value = SPECIAL_VALUE;
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
