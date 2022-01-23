#include "horizonline.h"
#include <QDebug>
#include <QRandomGenerator>

HorizonLine::HorizonLine(QObject *parent)
    : QObject{parent}
{
    timer   = new QTimer(this);
    floor1  = new QGraphicsPixmapItem(CONFIG->picture[0] , this);
    floor2  = new QGraphicsPixmapItem(CONFIG->picture[1] , this);

    initFloor();
    connect(this->timer, &QTimer::timeout,this, &HorizonLine::updatePos);
}

void HorizonLine::initFloor()
{
    floor1->setPos(0, CONFIG->yPOS);
    floor2->setPos(600, CONFIG->yPOS);
    floor1->setPixmap(CONFIG->picture[(QRandomGenerator::global()->bounded(2))]);
    floor1->setPixmap(CONFIG->picture[(QRandomGenerator::global()->bounded(2))]);
    this->setPos(0, 0);
    this->addToGroup(floor1);
    this->addToGroup(floor2);

}

HorizonLine::~HorizonLine()
{
    delete CONFIG;
    CONFIG = nullptr;
    qDebug() <<"horizonLine release";
}

void HorizonLine::speedUp(int speed)
{
    this->speed += speed;
}

void HorizonLine::updatePos()
{
    floor1->setX(floor1->x() - speed);
    floor2->setX(floor2->x() - speed);

    if(floor1->x() <= -600)
    {
        floor1->setX(floor1->x() + 1200);
        floor1->setPixmap(CONFIG->picture[(QRandomGenerator::global()->bounded(2))]);
    }
    else if(floor2->x() <= -600)
    {
        floor2->setX(floor2->x() + 1200);
        floor2->setPixmap(CONFIG->picture[(QRandomGenerator::global()->bounded(2))]);
    }
}
