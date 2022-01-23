#ifndef HORIZONLINE_H
#define HORIZONLINE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItemGroup>
#include "config.h"
#include <QTimer>

class HorizonLine : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit HorizonLine(QObject *parent = nullptr);

    ~HorizonLine();
    QTimer *timer;
    FloorConfig *CONFIG = new  FloorConfig;
    void speedUp(int speed);
    int speed = CONFIG->SPEED;

private:

    QGraphicsPixmapItem *floor1;
    QGraphicsPixmapItem *floor2;
    void initFloor();


private slots:
    void updatePos();


};

#endif // HORIZONLINE_H
