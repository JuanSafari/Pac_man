#ifndef GAME_H
#define GAME_H

#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <vector>

#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Collectible.h"

class Game {
public:
    Game();

    void start();

    void initializeScene();

    void initializeMap();

    void initializeScoreText();

    void initializePlayer();

    void initializeEnemies();

    void initializeView();

    void initializeTimer();

    void showGameOver();

    void gameLoop();

    void enqueueObjectToDelete(QGraphicsItem* item);

private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    QTimer* timer;

    Map* map;
    Player* player;
    std::vector<Enemy*> enemies;
    QGraphicsTextItem* scoreText;

    std::vector<QGraphicsItem*> itemsToDelete;
};

#endif //GAME_H
