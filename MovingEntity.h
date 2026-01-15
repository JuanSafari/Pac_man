#ifndef MOVINGENTITY_H
#define MOVINGENTITY_H

#include <QGraphicsRectItem>
#include "Map.h"

enum class Direction { Up, Down, Left, Right, None };

class MovingEntity : public QGraphicsRectItem {
public:
  MovingEntity(Map* map, int step);

protected:
  Map* map;
  int step;

  bool canMove(Direction dir);
  void setPosition(Direction direction);
};

#endif