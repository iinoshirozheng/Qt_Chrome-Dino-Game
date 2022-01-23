#include "obstacle.h"
#include <QRandomGenerator>

Obstacle::Obstacle(QObject *parent)
    : QObject{parent}
{
    initObstacle();
}

Obstacle::~Obstacle()
{
    delete CONFIG;
    CONFIG = nullptr;
    qDeleteAll(obstacle);
    obstacle.clear();
}

void Obstacle::setStartPos()
{
    for(int i = 0 ; i < obstacle.size() ; ++i)
        obstacle[i]->setX(obstacle[i]->x() + 1800);
}

void Obstacle::speedUp(int speed)
{
    this->speed += speed;
}

void Obstacle::initObstacle()
{
    int maxPos = 1200;
    for(int i = 0 ; i <  CONFIG->MAX_OBSTACLE_LENGTH ; ++i)
    {
        int randNum = QRandomGenerator::global()->bounded(6);
        obstacle.append( new QGraphicsPixmapItem( CONFIG->cactus_pictures[randNum], this));
        obstacle[i]->setPos( (maxPos += getRandomGap(true)), ((randNum < 3) ? CONFIG->SMALL_CACTUS_yPOS : CONFIG->BIG_CACTUS_yPOS));
        this->addToGroup(obstacle[i]);
    }
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Obstacle::updatePos);

}

int Obstacle::getRandomGap(bool isCactus = true)
{
    if(isCactus)
        return QRandomGenerator::global()->bounded(CONFIG->CACTUS_MIN_GAP, (int) (CONFIG->CACTUS_MIN_GAP *CONFIG->MAX_GAP_COEFFICIENT));
    else
        return QRandomGenerator::global()->bounded(CONFIG->PTERODACTYL_MIN_GAP, (int) (CONFIG->PTERODACTYL_MIN_GAP *CONFIG->MAX_GAP_COEFFICIENT));
}

void Obstacle::updatePos()
{

    for(int i = 0 ; i <  obstacle.size() ; ++i)
    {
        static int countPterodactylFrame = 0;
        if(isPterodactyl && obstacle[i]->pixmap().height() == 40)
        {
            ++countPterodactylFrame;
            if(obstacle[i]->pos().y() == 100)
            {
                obstacle[i]->setX(obstacle[i]->x() - speed);
                if(countPterodactylFrame%100 == 0)
                {
                    countPterodactylFrame = 0;
                    flutter = !flutter;
                    obstacle[i]->setPixmap(CONFIG->pterodactyl_pictures[flutter]);
                }
            }
            else
            {
                double randSpeed = (QRandomGenerator::global()->bounded(8, 20) /10.);
                obstacle[i]->setX(obstacle[i]->x() - speed * randSpeed);
                if(countPterodactylFrame % (int)(50*randSpeed) == 0)
                {
                    countPterodactylFrame = 0;
                    flutter = !flutter;
                    obstacle[i]->setPixmap(CONFIG->pterodactyl_pictures[flutter]);
                }
            }

        }
        else obstacle[i]->setX(obstacle[i]->x() - speed);

        if(obstacle[i]->x() < -obstacle[i]->pixmap().width())
        {
            int randNum = QRandomGenerator::global()->bounded(8);
            if(isPterodactyl) // 如果開啟翼龍模式且rand > 6
            {
                if(getPterodactyl && obstacle[i]->pixmap().height() == 40)  getPterodactyl = false;
                if(!getPterodactyl && randNum >= 6)
                {
                    getPterodactyl = true;
                    obstacle[i]->setPos( (obstacle.back()->x() + getRandomGap(false)) > 600 ? (obstacle.back()->x() + getRandomGap(false)) : 600,
                                        CONFIG->PTERODACTYL_yPOS[QRandomGenerator::global()->bounded(3)]);
                    obstacle[i]->setPixmap(CONFIG->pterodactyl_pictures[flutter]);
                    obstacle.append(obstacle.takeFirst());
                }

            }
            if (randNum < 6)
            {
                obstacle[i]->setPos((obstacle.back()->x() + getRandomGap(true)) > 600 ? ( obstacle.back()->x() + getRandomGap(true)) : 600,
                                    ((randNum < 3) ? CONFIG->SMALL_CACTUS_yPOS : CONFIG->BIG_CACTUS_yPOS));
                obstacle[i]->setPixmap(CONFIG->cactus_pictures[randNum]);
                obstacle.append(obstacle.takeFirst());
            }
        }

    }
}

void Obstacle::computeCollision(QGraphicsPixmapItem *dino)
{
    for (int i = 0 ; i < obstacle.size() ; ++i)
         if(obstacle[i]->collidesWithItem(dino)) emit signal_GAME_OVER();
}
