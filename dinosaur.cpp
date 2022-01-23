#include "dinosaur.h"
#include <QTimer>
#include <QRandomGenerator>

Dinosaur::Dinosaur(QObject *parent)
    : QObject{parent}
{
    initDinosaur();
}

Dinosaur::~Dinosaur()
{
    delete CONFIG;
    CONFIG = nullptr;
}

void Dinosaur::setPixmap()
{
    Dino->setPixmap(CONFIG->TRex_pictures[4]);
    QTimer::singleShot(500, [=](){
        Dino->setPixmap(CONFIG->TRex_pictures[5]);
    });

}

void Dinosaur::initDinosaur()
{

    Dino = new QGraphicsPixmapItem( CONFIG->TRex_pictures[0], this);
    Dino->setPos(0, floorPos);
    this->addToGroup(Dino);
    QTimer::singleShot(1000, this, &Dinosaur::blinkEyes);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Dinosaur::waitingToStart);
    timer->start(CONFIG->BLINK_TIMING);

}

void Dinosaur::blinkEyes()
{

    changeBlink();
    QTimer::singleShot(150, this, &Dinosaur::changeBlink);
    int times = QRandomGenerator::global()->bounded(3);
    if(times)
    {
        QTimer::singleShot(300, this, &Dinosaur::changeBlink);
        QTimer::singleShot(450, this, &Dinosaur::changeBlink);
        if(times == 2)
        {
            QTimer::singleShot(1000, this, &Dinosaur::changeBlink);
            QTimer::singleShot(1150, this, &Dinosaur::changeBlink);
        }
    }
}

void Dinosaur::updatePos()
{
    if(isJump)
    {

        if(isDuck || releaseKeyPress) velocity += (gravity * 1.5);
        else velocity += gravity;

        if(releaseKeyPress && Dino->y() <= 30) Dino->setY(Dino->y() + velocity/500.);
        else Dino->setY(Dino->y() + velocity/300.);

        if(Dino->y() >= floorPos)
        {
            Dino->setY(floorPos);
            velocity = 0;
            isJump = false;
            isRunning = true;
            releaseKeyPress = false;
        }

        if(Dino->y() <= 0) Dino->setY(0);

        if(isDuck) return;
//        qDebug() << Dino->y();
    }

    if(isRunning)
    {
        static int count = 0;

        if(Dino->y() != 93) return Dino->setY(93);

        if(Dino->x() != 44 && count%10 == 0) Dino->setX(Dino->x() + 1);
        if(!isStart && Dino->x() == 44)
        {
            isStart = true;
            emit startGame();
            qDebug() << "start";
        }

        if(count == 80)
        {
            changeRunning = !changeRunning;
            Dino->setPixmap(CONFIG->TRex_pictures[changeRunning +2]);
            count = 0;
        }
        ++count;
    }
    else if(isDuck)
    {
        static int count_duck = 0;

        if(Dino->y() != 110) return Dino->setY(110);

        if(count_duck == 80)
        {
            changeRunning = !changeRunning;
            Dino->setPixmap(CONFIG->TRex_Duck_pictures[changeRunning]);
            count_duck = 0;
        }

        ++count_duck;
    }
    emit signal_T_Rex_Pos(Dino);
//    qDebug() << "running = " << isRunning << " , duck = " << isDuck << ", jump = " << isJump;

}

void Dinosaur::changeBlink()
{
    static bool isBlink = false;
    isBlink = !isBlink;
    Dino->setPixmap(CONFIG->TRex_pictures[isBlink]);
}

void Dinosaur::waitingToStart()
{
    if(QRandomGenerator::global()->bounded(2))
        QTimer::singleShot(0, this, &Dinosaur::blinkEyes);
}

void Dinosaur::duck()
{
    if(!isStart) return;
    isDuck = true;
    isRunning = false;
    isJump = false;
    changeRunning = false;
    Dino->setPixmap(CONFIG->TRex_Duck_pictures[0]);

}


void Dinosaur::start()
{

    timer->stop();
    disconnect(timer, &QTimer::timeout, this, &Dinosaur::waitingToStart);
    connect(timer, &QTimer::timeout, this, &Dinosaur::updatePos);
    timer->start(1);
    jump();

}

void Dinosaur::jump()
{
    if(Dino->y() != floorPos) return;

    isJump = true;
    isRunning = false;
    Dino->setPixmap(CONFIG->TRex_pictures[0]);
    velocity = - 97*2.4405;
}

void Dinosaur::smallJump()
{
    if(!isStart) return;
    else if(Dino->y() >30) releaseKeyPress = true;
}

void Dinosaur::run()
{
    isRunning = true;
    isDuck = false;
    Dino->setPixmap(CONFIG->TRex_pictures[0]);
}
