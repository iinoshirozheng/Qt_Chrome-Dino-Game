#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QGraphicsPixmapItem>

#include "horizonline.h"
#include "cloud.h"
#include "nightmode.h"
#include "obstacle.h"
#include "dinosaur.h"
#include "gamecounter.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    ~Scene();

private:
    GameConfig *CONFIG = new GameConfig;
    void initBackGround();

    void start();
    void stopGame();
    void gameOver();
    void loadGame(bool show);
    void showItem(int mSec, QGraphicsPixmapItem *item, bool show);
    void speedUp();

    HorizonLine *floor;
    NightMode *sky;
    Cloud *clouds;
    Obstacle *obstacle;
    Dinosaur *dino;
    GameCounter *counter;

    bool startGame = false;
    bool isStop = false;
    bool isGameOver = false;

    QGraphicsPixmapItem *game_over_picture;
    QGraphicsPixmapItem *loading_picture[6];




    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event) override;

    // QGraphicsScene interface
protected:
    void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // SCENE_H
