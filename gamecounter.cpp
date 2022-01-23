#include "gamecounter.h"

GameCounter::GameCounter(QObject *parent)
    : QObject{parent}
{
    timer = new QTimer(this);
    initScore();
    connect(timer, &QTimer::timeout, this, &GameCounter::updateScore);
}

GameCounter::~GameCounter()
{
    delete CONFIG;
    CONFIG = nullptr;
    qDeleteAll(score);
    score.clear();
}

void GameCounter::resetScore()
{

    qDeleteAll(score);
    score.clear();
    myScore = 0;
    initScore();

}

void GameCounter::updateScore()
{
    ++myScore;
    if(myScore % CONFIG->CHANGE_MODE_SCORE == 0) emit changeMode();
    if(myScore % CONFIG->CHANGE_SPEED == 0) emit changeSpeed();
    int getScore = myScore;
    int i = 0;
    while(getScore)
    {
        if(score.size() <= i) addNewScore();
        score[i]->setPixmap(CONFIG->number_pictures[getScore%10]);
        getScore /= 10;
        ++i;
    }
}

void GameCounter::addNewScore()
{
    int last_xPos = score.last()->x();
    score.append(new QGraphicsPixmapItem(CONFIG->number_pictures[0], this));
    score.last()->setPos( last_xPos - 11 , CONFIG->yPOS);
    this->addToGroup(score.last());
}

void GameCounter::initScore()
{
    for(int i = 0 ; i < CONFIG->MAX_SCORE_UNIT ; ++i)
    {
        score.append(new QGraphicsPixmapItem(CONFIG->number_pictures[0], this));
        score[i]->setPos(CONFIG->xPOS - 11*i , CONFIG->yPOS);
        this->addToGroup(score[i]);
    }
}
