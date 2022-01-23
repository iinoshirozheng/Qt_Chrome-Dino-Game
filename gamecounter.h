#ifndef GAMECOUNTER_H
#define GAMECOUNTER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItemGroup>
#include "config.h"
#include <QTimer>
#include <QList>

class GameCounter : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit GameCounter(QObject *parent = nullptr);
    ~GameCounter();
    QTimer *timer;
    void resetScore();

private:
    ScoreConfig *CONFIG = new ScoreConfig;
    QList <QGraphicsPixmapItem*> score;
    void updateScore();
    int myScore = 0;
    void addNewScore();
    void initScore();

signals:
    void changeMode();
    void changeSpeed();

};

#endif // GAMECOUNTER_H
