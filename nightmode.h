#ifndef NIGHTMODE_H
#define NIGHTMODE_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "config.h"
#include <QList>

class NightMode :public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit NightMode(QObject *parent = nullptr);
    ~NightMode();
    QTimer *night_mode_timer;

    void startChangeModeTimer();
private:
    SkyConfig *CONFIG = new SkyConfig;

    QList <QGraphicsPixmapItem*> stars;
    QGraphicsPixmapItem *moon;

    int countMoon = 0;


    QGraphicsPixmapItem* day;
    QGraphicsPixmapItem* night;
    QTimer *change_mode_timer;
    QPixmap *change_day_background;
    bool isMorning = true;

    void initBackground();
    void initStars();
    void getRandomStars(int num);
    void initMoon();



private slots:
    void updatePos();
    void updateTransparency();

};

#endif // NIGHTMODE_H
