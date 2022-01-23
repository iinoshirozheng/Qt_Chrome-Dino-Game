#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItemGroup>
#include "config.h"
#include <QTimer>
#include <QGraphicsItem>

class Obstacle : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    ObstacleConfig *CONFIG = new ObstacleConfig;
    int speed = CONFIG->SPEED;
    explicit Obstacle(QObject *parent = nullptr);
    ~Obstacle();
    void setStartPos();
    void speedUp(int speed);

    QTimer *timer;
private:

    void initObstacle();
    int getRandomGap(bool isCactus);

    QList <QGraphicsPixmapItem*> obstacle;

    bool getPterodactyl = false;
    bool isPterodactyl = true;

    bool flutter = false;
    void updatePos();


public slots:
    void computeCollision(QGraphicsPixmapItem *);
signals:
    void signal_GAME_OVER();

};

#endif // OBSTACLE_H
