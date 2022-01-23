#include "./ui_widget.h"
#include "widget.h"



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(WIDGET_WIDTH + FRAME_SIEZ, WIDGET_HEIGHT + FRAME_SIEZ);
    scene->setSceneRect(0, 0, WIDGET_WIDTH, WIDGET_HEIGHT);
    ui->graphicsView->setScene(scene);
}

Widget::~Widget()
{
    delete ui;
}

