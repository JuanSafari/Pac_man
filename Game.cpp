#include "Game.h"

Game::Game() {
}

void Game::start() {
    initializeScene();
    initializeMap();
    initializeScoreText();
    initializePlayer();
    initializeEnemies();
    initializeView();
    initializeTimer();
}

void Game::initializeScene() {
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, Map::width * Map::tileSize, Map::height * Map::tileSize);
}

void Game::initializeMap() {
    map = new Map();

    map->addSimpleCollectible(13, 2);
    map->addSimpleCollectible(4, 3);
    map->addSimpleCollectible(5, 1);
    map->addSimpleCollectible(10, 11);
    map->addSimpleCollectible(1, 15);
    map->addSimpleCollectible(15, 10);


    map->addSpecialCollectible(7, 7);
    map->addSpecialCollectible(12, 15);
    map->draw(scene);
}

void Game::initializeScoreText() {
    scoreText = new QGraphicsTextItem();
    scoreText->setPlainText("Score: 0");
    scoreText->setDefaultTextColor(Qt::white);
    scoreText->setFont(QFont("Arial", 16));
    scoreText->setPos(10, 10);
    scene->addItem(scoreText);
}

void Game::initializePlayer() {
    player = new Player(map, scoreText);
    scene->addItem(player);
    player->setFocus();
}

void Game::initializeEnemies() {
    map->addEnemy(15, 2, player);
    map->addEnemy(11, 10, player);

    enemies = map->getEnemies();

    for (Enemy* enemy: enemies) {
        scene->addItem(enemy);
    }
}

void Game::initializeView() {
    view = new QGraphicsView(scene);
    view->show();
}

void Game::initializeTimer() {
    timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [&]() {
        gameLoop();
    });
    timer->start(FRAME_TIME);
}

void Game::showGameOver(QString message) {
    QGraphicsRectItem* overlay = new QGraphicsRectItem(scene->sceneRect());
    overlay->setBrush(Qt::black);
    scene->addItem(overlay);

    QGraphicsTextItem* gameOverText = new QGraphicsTextItem(message);
    gameOverText->setDefaultTextColor(Qt::red);
    gameOverText->setFont(QFont("Arial", 32));
    gameOverText->setPos(
        scene->width() / 2 - 100,
        scene->height() / 2 - 20
    );
    scene->addItem(gameOverText);
}

void Game::gameLoop() {
    scene->advance();

    for (Enemy* enemy: enemies) {
        if (!enemy->isAlive()) {
            itemsToDelete.push_back(enemy);
        }
    }

    for (QGraphicsItem* item: itemsToDelete) {
        scene->removeItem(item);
        delete item;
    }
    itemsToDelete.clear();

    for (auto it = enemies.begin(); it != enemies.end();) {
        if (!(*it)->isAlive()) {
            it = enemies.erase(it);
        } else {
            it++;
        }
    }

    for (Enemy* enemy: enemies) {
        if (player->isPowered()) {
            enemy->setFrightened(true);
        } else {
            enemy->setFrightened(false);
        }
    }

    if (enemies.empty() && map->getCollectibles().empty()) {
        timer->stop();
        showGameOver("YOU WIN!");
    }

    if (!player->isVisible()) {
        timer->stop();
        showGameOver("GAME OVER");
    }
}
