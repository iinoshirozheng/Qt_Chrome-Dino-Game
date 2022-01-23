#ifndef CLOUD_H
#define CLOUD_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItemGroup>
#include "config.h"
#include <QTimer>
#include <QList>

class Cloud :public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit Cloud(QObject *parent = nullptr);
    ~Cloud();
    QTimer* timer;

private:
    CloudConfig* CONFIG;
    QList <QGraphicsPixmapItem*> clouds;
    int max_xPos;

    void initCloudList();

private slots:
    void UpdatePos();

};

#endif // CLOUD_H
