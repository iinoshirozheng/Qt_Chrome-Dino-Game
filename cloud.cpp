#include "cloud.h"
#include <QRandomGenerator>

Cloud::Cloud(QObject *parent)
    : QObject{parent}
{
    CONFIG  = new CloudConfig;
    timer   = new QTimer(this);

    initCloudList(); // Init
    connect(this->timer, &QTimer::timeout, this, &Cloud::UpdatePos);

}

Cloud::~Cloud()
{
    delete CONFIG;
    CONFIG = nullptr;
    qDeleteAll(clouds);
    clouds.clear();

    qDebug() << "clouds release";
}

void Cloud::UpdatePos()
{
    max_xPos -= CONFIG->SPEED;
    for(int i = 0 ; i < clouds.size(); ++i)
    {
        clouds[i]->setX(clouds[i]->x() - CONFIG->SPEED);
        if(clouds[i]->x() <= -CONFIG->picture.width())
            clouds[i]->setPos(max_xPos += QRandomGenerator::global()->bounded(CONFIG->MIN_CLOUD_GAP, CONFIG->MAX_CLOUD_GAP),
                              QRandomGenerator::global()->bounded(CONFIG->MAX_SKY_LEVEL, CONFIG->MIN_SKY_LEVEL));
    }
}

void Cloud::initCloudList()
{
    int count = 0;

    for(int i = 0; i < CONFIG->MAX_CLOUDS; ++i)
    {
        clouds.append(new QGraphicsPixmapItem(CONFIG->picture, this));
        clouds[i]->setPos(QPointF(count += QRandomGenerator::global()->bounded(CONFIG->MIN_CLOUD_GAP, CONFIG->MAX_CLOUD_GAP),
                                  QRandomGenerator::global()->bounded(CONFIG->MAX_SKY_LEVEL, CONFIG->MIN_SKY_LEVEL)));
        this->addToGroup(clouds[i]);
    }
    max_xPos = clouds.last()->x();
}
