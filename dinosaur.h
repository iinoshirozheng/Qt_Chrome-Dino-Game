#ifndef DINOSAUR_H
#define DINOSAUR_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItemGroup>
#include "config.h"

class Dinosaur : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit Dinosaur(QObject *parent = nullptr);
    ~Dinosaur();

    QTimer *timer;
    void setPixmap();
    void start();
    void jump();
    void smallJump();
    void duck();
    void run();


private:
    TRexConfig *CONFIG = new TRexConfig;
    QGraphicsPixmapItem* Dino;
    bool isStart = false;
    int floorPos = CONFIG->yPos;
    bool changeRunning = false;

    double gravity = 1.;
    double velocity = 0;
    void updatePos();

    void changeBlink();
    void waitingToStart();
    void waitIsStart();
    void initDinosaur();
    void blinkEyes();



    bool isJump = false;
    bool isRunning = false;
    bool isDuck = false;
    bool releaseKeyPress = false;

signals:
    void startGame();
    void signal_T_Rex_Pos(QGraphicsPixmapItem*);

};

#endif // DINOSAUR_H
