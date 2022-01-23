#include "dino_image.h"
#include <QDebug>
Dino_Image::Dino_Image()
{

    ////////////////////////////地板的圖片//////////////////////////////
    floor.append(QRect(2, 54, 600, 12));
    floor.append(QRect(602, 54, 600, 12));

    ////////////////////////////雲朵的圖片//////////////////////////////
    cloud = QRect(86, 2, 46, 14); // 雲朵

    ////////////////////////////小仙人掌的圖片///////////////////////////
    for(int i = 0; i < 3 ; ++i) // 小仙人掌
        small_cacti.append(QRect(228 + (pow(2,i)-1)*17, 2, 17*(i+1), 35));

    ////////////////////////////大仙人掌的圖片///////////////////////////
    for(int i = 0; i < 3 ; ++i) // 大仙人掌
        big_cacti.append(QRect(332 +(pow(2,i)-1)*25 , 2, 25 *(i+1), 50));

    ////////////////////////////月亮的圖片//////////////////////////////
    int moon_widget ; // moon widget
    int moon_xPos = 484;
    for(int i = 0 ; i < 7 ; ++i)
    {
        moon_widget = (i!=3 ? 20 : 40) ;
        moon.append(QRect(moon_xPos, 2, moon_widget, 40));
        moon_xPos += moon_widget;
    }

    ////////////////////////////星星的圖片//////////////////////////////
    for(int i = 0; i < 3 ; ++i) // stars 1~3
        stars.append(QRect(645, 2 + i*9, 9, 9));

    ////////////////////////////翼龍的圖片//////////////////////////////
    for(int i = 0; i < 2 ; ++i) // 翼龍拍打翅膀
        this->pterodactyl.append(QRect(134 + i*46, 2, 46, 40));

    ////////////////////////////暴龍的圖片//////////////////////////////
    for(int i = 0; i < 6 ; ++i) // 暴龍 1~6 表情與跑步
        T_Rex.append(QRect(848 + i*44 , 2, 44, 47));

    ////////////////////////////暴龍閃躲的圖片///////////////////////////
    this->T_Rex_Duck.append(QRect(1112, 19,59, 30)); // 暴龍蹲下跑步
    this->T_Rex_Duck.append(QRect(1171, 19,59, 30));

    ////////////////////////////數字的圖片//////////////////////////////
    for(int i = 0; i < 10 ; ++i) // 數字 0~9
        this->numbers.append(QRect(655 + i*10, 2, 10, 11));

    ////////////////////////////任意鍵繼續圖示//////////////////////////
    for(int i = 0; i < 6 ; ++i) // 任意鍵繼續圖示
        this->press_any_key.append(QRect(74 + i*36, 68, 36, 32));

    ////////////////////////////game over圖示/////////////////////////
    this->game_over = QRect(655, 15, 191, 11); // game over

}

Dino_Image::~Dino_Image()
{
    floor.clear();
    small_cacti.clear();
    big_cacti.clear();
    moon.clear();
    stars.clear();
    pterodactyl.clear();
    T_Rex.clear();
    T_Rex_Duck.clear();
    numbers.clear();
    press_any_key.clear();
}
