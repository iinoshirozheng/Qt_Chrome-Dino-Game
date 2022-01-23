#ifndef DINO_IMAGE_H
#define DINO_IMAGE_H
#include <QRect>
#include <QList>
#include <QString>

class Dino_Image
{
public:
    Dino_Image();
    ~Dino_Image();
    QString Dino_Path = ":/image/DinoScript.png";
    QList <QRect> floor;
    QRect cloud;

    QList <QRect> small_cacti;
    QList <QRect> big_cacti;
    QList <QRect> moon;
    QList <QRect> stars;

    QList <QRect> T_Rex;
    QList <QRect> T_Rex_Duck;
    QList <QRect> pterodactyl;

    QList <QRect> numbers;
    QList <QRect> press_any_key;
    QRect game_over;
};

#endif // DINO_IMAGE_H
