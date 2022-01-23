#include "scene.h"
#include <QKeyEvent>

Scene::Scene(QObject *parent)
    : QGraphicsScene{parent}
{
    initBackGround();
}

Scene::~Scene()
{
    this->removeItem(sky);
    this->removeItem(floor);
    this->removeItem(clouds);
    this->removeItem(obstacle);
    this->removeItem(dino);
    this->removeItem(counter);
    delete game_over_picture;
    game_over_picture = nullptr;
    for(int i = 0 ; i < 6 ; ++i)
    {
        delete loading_picture[i];
        loading_picture[i] = nullptr;
    }

    qDebug() << "scene release";
}

void Scene::initBackGround()
{
    sky = new NightMode(this);
    floor = new HorizonLine(this);
    clouds = new Cloud(this);
    clouds->timer->start(60);
    obstacle = new Obstacle(this);
    dino = new Dinosaur(this);
    counter = new GameCounter(this);
    connect(dino, &Dinosaur::startGame, this, &Scene::start);
    connect(counter, &GameCounter::changeMode, sky, &NightMode::startChangeModeTimer);
    connect(dino, &Dinosaur::signal_T_Rex_Pos, obstacle, &Obstacle::computeCollision);
    connect(obstacle, &Obstacle::signal_GAME_OVER, this, &Scene::gameOver);
//    connect(counter, &GameCounter::changeMode, this, &Scene::speedUp);


    this->addItem(sky);
    this->addItem(floor);
    this->addItem(clouds);
    this->addItem(obstacle);
    this->addItem(dino);
    this->addItem(counter);

    game_over_picture = new QGraphicsPixmapItem(CONFIG->game_over_pictures);
    game_over_picture->setPos((int)((WIDGET_WIDTH - game_over_picture->pixmap().width())/2),
                              (int)((WIDGET_HEIGHT - game_over_picture->pixmap().height())/3));
    for(int i = 0; i < 6 ;++i)
    {
        loading_picture[i] = new QGraphicsPixmapItem(CONFIG->loading_pictures[i]);
        loading_picture[i]->setPos((int)((WIDGET_WIDTH - loading_picture[i]->pixmap().width())/2),
                                  (int)((WIDGET_HEIGHT - loading_picture[i]->pixmap().height())/3*2));
    }

}

void Scene::start()
{
    if(isGameOver)
    {
        this->removeItem(game_over_picture);
        obstacle->setStartPos();
        isGameOver = false;
        counter->resetScore();
        obstacle->speed = GAME_SPEED;
        floor->speed = GAME_SPEED;
    }
    loadGame(false);
    floor->timer->start(GAME_TIMER_mSEC);
    obstacle->timer->start(GAME_TIMER_mSEC);
    clouds->timer->start(BASE_TIMER_mSEC);
    dino->timer->start(GAME_SPEED);
    counter->timer->start(100);
    isStop = false;

}

void Scene::stopGame()
{
    floor->timer->stop();
    obstacle->timer->stop();
    clouds->timer->stop();
    dino->timer->stop();
    counter->timer->stop();
    isStop = true;
    loadGame(true);
}

void Scene::gameOver()
{
    floor->timer->stop();
    obstacle->timer->stop();
    clouds->timer->start(60);
    dino->timer->stop();
    counter->timer->stop();
    dino->setPixmap();
    isGameOver = true;
    this->addItem(game_over_picture);
    loadGame(true);
}

void Scene::loadGame(bool show)
{
    for(int i = 0 ; i < 6 ; ++i)
    {
        if(isGameOver) loading_picture[i]->setY((int)((WIDGET_HEIGHT - loading_picture[i]->pixmap().height())/3*2));
        else loading_picture[i]->setY((int)((WIDGET_HEIGHT - loading_picture[i]->pixmap().height())/2));
        showItem(100 * (i+1), loading_picture[i], show);
    }
}

void Scene::showItem( int mSec, QGraphicsPixmapItem *item, bool show)
{
    if(show) QTimer::singleShot(mSec, [=](){this->addItem(item);});
    else this->removeItem(item);
}

void Scene::speedUp()
{
    obstacle->speedUp(1);
    floor->speedUp(1);
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Space :

        if (!startGame && !event->isAutoRepeat())
        {
            dino->start();
            startGame = true;
            qDebug() << "pressKey start";
        }
        if(isStop || isGameOver) return start();
        dino->jump();
        break;

    case Qt::Key_Up:
        dino->jump();
        break;

    case Qt::Key_Down:
        if(!event->isAutoRepeat() && !isGameOver) dino->duck();
        break;

    case Qt::Key_Escape:
        stopGame();
        break;

    }
}

void Scene::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Space:
        dino->smallJump();
        break;

    case Qt::Key_Up:
        dino->smallJump();
        break;

    case Qt::Key_Down:
        if(!event->isAutoRepeat()) dino->run();
        break;
    }
}


