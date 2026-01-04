#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include <QGraphicsEllipseItem>

enum class CollectibleType {
    Simple,
    Special
};

class Collectible : public QGraphicsEllipseItem {
public:
    Collectible(int x, int y, int size, CollectibleType type);

    void draw(QGraphicsScene* scene);

    CollectibleType getType() const;

    int getValue() const;

private:
    CollectibleType type;
    int value;
};


#endif //COLLECTIBLE_H
