#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include <QGraphicsEllipseItem>

#define NORMAL_VALUE 10
#define SPECIAL_VALUE 50

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
