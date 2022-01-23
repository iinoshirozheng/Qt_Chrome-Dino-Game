#include "nightmode.h"
#include <QRandomGenerator>

NightMode::NightMode(QObject *parent)
    : QObject{parent}
{
    initBackground();
}

NightMode::~NightMode()
{
    if(CONFIG->NIGHT_MODE)
    {
        qDeleteAll(stars);
        stars.clear();
    }

    delete change_day_background;
    change_day_background = nullptr;
    delete CONFIG;
    CONFIG = nullptr;
    qDebug() << "nightmode release";
}

void NightMode::initBackground()
{
    if(CONFIG->NIGHT_MODE)
    {
        QPixmap nigit_background = QPixmap(WIDGET_WIDTH, WIDGET_HEIGHT);
        nigit_background.fill(Qt::black);
        night = new QGraphicsPixmapItem(nigit_background, this);
        change_mode_timer = new QTimer(this);
        night_mode_timer = new QTimer(this);
        connect(change_mode_timer, &QTimer::timeout, this, &NightMode::updateTransparency);
        connect(night_mode_timer, &QTimer::timeout, this, &NightMode::updatePos);
        this->addToGroup(night);
        initStars();
        initMoon();
    }
    else
    {
        change_mode_timer = nullptr;
        night = nullptr;
    }

    change_day_background = new QPixmap(WIDGET_WIDTH, WIDGET_HEIGHT);
    change_day_background->fill(Qt::white);

    day   = new QGraphicsPixmapItem(*change_day_background, this);
    this->addToGroup(day);

}

void NightMode::updateTransparency()
{
    static int transparency = isMorning ? 255 : 0;
    if (isMorning) change_day_background->fill(QColor(255, 255, 255, --transparency));
    else change_day_background->fill(QColor(255, 255, 255, ++transparency));

    day->setPixmap(*change_day_background);

    if(transparency == 0 || transparency == 255)
    {
        change_mode_timer->stop();
        if(transparency == 255) night_mode_timer->stop();
        isMorning = !isMorning;
        if(!isMorning) QTimer::singleShot(CONFIG->NIGHT_DURATION, this, &NightMode::startChangeModeTimer);

    }
//    qDebug() << transparency;
}

void NightMode::initStars()
{
    if(CONFIG->NIGHT_MODE)
    {
        for(int i = 0 ; i < CONFIG->MAX_STAR ; ++i)
            stars.append(new QGraphicsPixmapItem(CONFIG->star_pictures[QRandomGenerator::global()->bounded(3)], this));
        getRandomStars(CONFIG->MAX_STAR);
    }
    else
    {
        qDeleteAll(stars);
        stars.clear();
    }
}

void NightMode::getRandomStars(int num)
{
    int randomRange = (int) WIDGET_WIDTH/num;
    int xPos = 0;
    for(int i = 0 ; i < stars.size() ; ++i)
    {
        stars[i]->setPos(xPos + QRandomGenerator::global()->bounded(randomRange),
                         QRandomGenerator::global()->bounded(20, CONFIG->STAR_MAX_yPOS));
        this->addToGroup(stars[i]);
        xPos += randomRange;
    }

}

void NightMode::initMoon()
{
    if(CONFIG->NIGHT_MODE)
    {
        moon = new QGraphicsPixmapItem(CONFIG->moon_pictures[0], this);
        moon->setPos(CONFIG->MOON_xPOS, CONFIG->MOON_yPOS);
        this->addToGroup(moon);
    }
}

void NightMode::updatePos()
{
//    qDebug() << isMorning;

    moon->setX(moon->x() - CONFIG->SPEED);
    if(moon->x() <= -50)
    {
        countMoon = (countMoon == 6 ) ? 0 : (++countMoon);
//        qDebug() << countMoon;
        moon->setPixmap(CONFIG->moon_pictures[countMoon]);
        moon->setX(650);
    }
    for (int i = 0 ; i < stars.size(); ++i)
    {
        stars[i]->setX(stars[i]->x() - CONFIG->SPEED);
        if(stars[i]->x() <= -50) stars[i]->setPos(650, QRandomGenerator::global()->bounded(20, CONFIG->STAR_MAX_yPOS));
    }

}

void NightMode::startChangeModeTimer()
{
    if(!CONFIG->NIGHT_MODE) return;
    if(isMorning)
    {
        countMoon = (countMoon ==6 ) ? 0 : ++countMoon;
        moon->setPixmap(CONFIG->moon_pictures[countMoon]);
        getRandomStars(CONFIG->MAX_STAR);
    }
    night_mode_timer->start(CONFIG->TIMER_mSEC);
    change_mode_timer->start(CONFIG->CHANGE_MODE_TIMER);

}
