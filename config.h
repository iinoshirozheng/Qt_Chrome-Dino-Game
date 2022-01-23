#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QRect>
#include "dino_image.h"
#include <QPixmap>

#define FRAME_SIEZ        42
#define WIDGET_WIDTH      600
#define WIDGET_HEIGHT     180 // 150
#define DINO_PATH         QString(":/image/DinoScript.png")
#define BASE_TIMER_mSEC   30
#define GAME_TIMER_mSEC   3
#define GAME_SPEED        1
#define GAME_CHANGE_SPEED 0.05


const static Dino_Image sprite_image = Dino_Image();

struct FloorConfig
{
    int TIMER_mSEC = GAME_TIMER_mSEC;
    int SPEED = GAME_SPEED;

    int xPOS = 0;
    int yPOS = 127;
    QPixmap picture[2]  = {QPixmap(DINO_PATH).copy(sprite_image.floor[0]),
                           QPixmap(DINO_PATH).copy(sprite_image.floor[1])};
};

struct CloudConfig
{
    int MAX_CLOUD_GAP = 400;
    int MIN_CLOUD_GAP = 100;

    int MAX_SKY_LEVEL = 30;
    int MIN_SKY_LEVEL = 71;

    int MAX_CLOUDS = 4;

    int TIMER_mSEC = BASE_TIMER_mSEC;
    int SPEED = 2;


    QPixmap picture = QPixmap(DINO_PATH).copy(sprite_image.cloud);
};

struct SkyConfig
{
    int  MODE_CHANGE_mSEC = 5;
    int  NIGHT_DURATION = 5000;
    bool NIGHT_MODE = true;
    int  SPEED = 1;
    int  TIMER_mSEC = 50;
    int  CHANGE_MODE_TIMER = 4;

    QPixmap star_pictures[3] = {QPixmap(DINO_PATH).copy(sprite_image.stars[0]),
                                QPixmap(DINO_PATH).copy(sprite_image.stars[1]),
                                QPixmap(DINO_PATH).copy(sprite_image.stars[2])};
    int MAX_STAR = 2;
    int STAR_MAX_yPOS = 70;

    QPixmap moon_pictures[7] = {QPixmap(DINO_PATH).copy(sprite_image.moon[0]),
                                QPixmap(DINO_PATH).copy(sprite_image.moon[1]),
                                QPixmap(DINO_PATH).copy(sprite_image.moon[2]),
                                QPixmap(DINO_PATH).copy(sprite_image.moon[3]),
                                QPixmap(DINO_PATH).copy(sprite_image.moon[4]),
                                QPixmap(DINO_PATH).copy(sprite_image.moon[5]),
                                QPixmap(DINO_PATH).copy(sprite_image.moon[6])};
    int MOON_xPOS = 550;
    int MOON_yPOS = 30;
};

struct ObstacleConfig
{
    int TIMER_mSEC = GAME_TIMER_mSEC;
    int SPEED = GAME_SPEED;

    double MAX_GAP_COEFFICIENT = 1.5;
    int MAX_OBSTACLE_LENGTH = 3;
    int MAX_OBSTACLE_DUPLICATION = 2;
    int DEFAULT_xPOS = 600;

    int CACTUS_MIN_GAP = 300;
    int SMALL_CACTUS_yPOS = 105;
    int BIG_CACTUS_yPOS = 90;

    int PTERODACTYL_MIN_GAP = 400;
    int PTERODACTYL_yPOS[3] = {100, 70, 50};
    int PTERODACTYL_TIMER_mSEC = 120;

    QPixmap pterodactyl_pictures[2] = {QPixmap(DINO_PATH).copy(sprite_image.pterodactyl[0]),
                                       QPixmap(DINO_PATH).copy(sprite_image.pterodactyl[1])};

    QPixmap cactus_pictures[6] = {QPixmap(DINO_PATH).copy(sprite_image.small_cacti[0]),
                                  QPixmap(DINO_PATH).copy(sprite_image.small_cacti[1]),
                                  QPixmap(DINO_PATH).copy(sprite_image.small_cacti[2]),
                                  QPixmap(DINO_PATH).copy(sprite_image.big_cacti[0]),
                                  QPixmap(DINO_PATH).copy(sprite_image.big_cacti[1]),
                                  QPixmap(DINO_PATH).copy(sprite_image.big_cacti[2])};

};

struct TRexConfig
{
    int BLINK_TIMING = 10000;
    int yPos = 93;
    QPixmap TRex_pictures[6] = {QPixmap(DINO_PATH).copy(sprite_image.T_Rex.at(0)),
                                QPixmap(DINO_PATH).copy(sprite_image.T_Rex.at(1)),
                                QPixmap(DINO_PATH).copy(sprite_image.T_Rex.at(2)),
                                QPixmap(DINO_PATH).copy(sprite_image.T_Rex.at(3)),
                                QPixmap(DINO_PATH).copy(sprite_image.T_Rex.at(4)),
                                QPixmap(DINO_PATH).copy(sprite_image.T_Rex.at(5))};

    QPixmap TRex_Duck_pictures[2] = {QPixmap(DINO_PATH).copy(sprite_image.T_Rex_Duck.at(0)),
                                QPixmap(DINO_PATH).copy(sprite_image.T_Rex_Duck.at(1))};


};

struct GameConfig
{
    QPixmap game_over_pictures = {QPixmap(DINO_PATH).copy(sprite_image.game_over)};
    QPixmap loading_pictures[6] = {QPixmap(DINO_PATH).copy(sprite_image.press_any_key.at(0)),
                                   QPixmap(DINO_PATH).copy(sprite_image.press_any_key.at(1)),
                                   QPixmap(DINO_PATH).copy(sprite_image.press_any_key.at(2)),
                                   QPixmap(DINO_PATH).copy(sprite_image.press_any_key.at(3)),
                                   QPixmap(DINO_PATH).copy(sprite_image.press_any_key.at(4)),
                                   QPixmap(DINO_PATH).copy(sprite_image.press_any_key.at(5))};
};

struct ScoreConfig
{
    QPixmap number_pictures[10] = {QPixmap(DINO_PATH).copy(sprite_image.numbers.at(0)),
                                   QPixmap(DINO_PATH).copy(sprite_image.numbers.at(1)),
                                   QPixmap(DINO_PATH).copy(sprite_image.numbers.at(2)),
                                   QPixmap(DINO_PATH).copy(sprite_image.numbers.at(3)),
                                   QPixmap(DINO_PATH).copy(sprite_image.numbers.at(4)),
                                   QPixmap(DINO_PATH).copy(sprite_image.numbers.at(5)),
                                   QPixmap(DINO_PATH).copy(sprite_image.numbers.at(6)),
                                   QPixmap(DINO_PATH).copy(sprite_image.numbers.at(7)),
                                   QPixmap(DINO_PATH).copy(sprite_image.numbers.at(8)),
                                   QPixmap(DINO_PATH).copy(sprite_image.numbers.at(9))};
    int FLASH_ITERATIONS = 3;
    int MAX_SCORE_UNIT = 5;
    int yPOS = 5;
    int xPOS = 600 -15;
    int CHANGE_MODE_SCORE = 500;
    int CHANGE_SPEED = 100;
};

#endif // CONFIG_H
